#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <openssl/sha.h>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

std::array<uint8_t, SHA_DIGEST_LENGTH> sha1(const std::string& msg)
{
    std::array<uint8_t, SHA_DIGEST_LENGTH> digest;

    SHA1(
        reinterpret_cast<const unsigned char*>(msg.data()),
        msg.size(),
        digest.data());

    return digest;
}

uint32_t sha1_truncated_bits(const std::string& msg, int n)
{
    auto digest = sha1(msg);

    uint32_t value = 0;
    value |= (static_cast<uint32_t>(digest[0]) << 24);
    value |= (static_cast<uint32_t>(digest[1]) << 16);
    value |= (static_cast<uint32_t>(digest[2]) << 8);
    value |= (static_cast<uint32_t>(digest[3]));

    int shift = 32 - n;
    if (shift > 0)
        value >>= shift;

    return value;
}

std::string random_message(std::mt19937& rng, size_t length = 16)
{
    static const char charset[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::uniform_int_distribution<int> dist(0, sizeof(charset) - 2);

    std::string msg;
    msg.reserve(length);

    for (size_t i = 0; i < length; ++i)
        msg.push_back(charset[dist(rng)]);

    return msg;
}

uint64_t collision_attack_sample(int n, std::mt19937& rng)
{
    std::unordered_map<uint32_t, std::string> seen;

    uint64_t iterations = 0;

    while (true)
    {
        std::string msg = random_message(rng);
        uint32_t hash = sha1_truncated_bits(msg, n);

        ++iterations;

        auto it = seen.find(hash);

        if (it != seen.end() && it->second != msg)
            return iterations;

        seen[hash] = msg;
    }
}

uint64_t preimage_attack_sample(int n,
                                const std::string& target_message,
                                std::mt19937& rng)
{
    uint32_t target_hash = sha1_truncated_bits(target_message, n);

    uint64_t iterations = 0;

    while (true)
    {
        std::string msg = random_message(rng);

        if (msg == target_message)
            continue;

        ++iterations;

        if (sha1_truncated_bits(msg, n) == target_hash)
            return iterations;
    }
}

int main()
{
    std::random_device rd;
    std::mt19937 rng(rd());

    std::vector<int> bit_sizes =
    {
        8, 10, 12, 14, 16, 18, 20, 22
    };

    const int SAMPLES = 50;

    std::string target_message = "fixed message for preimage";

    std::ofstream output("results.csv");

    output << "type,bits,sample,iterations\n";

    for (int bits : bit_sizes)
    {
        std::cout << "Running " << bits << "-bit experiments...\n";

        for (int sample = 0; sample < SAMPLES; ++sample)
        {
            uint64_t iterations = collision_attack_sample(bits, rng);

            output << "collision,"
                   << bits << ","
                   << sample << ","
                   << iterations << "\n";
        }

        for (int sample = 0; sample < SAMPLES; ++sample)
        {
            uint64_t iterations =
                preimage_attack_sample(bits, target_message, rng);

            output << "preimage,"
                   << bits << ","
                   << sample << ","
                   << iterations << "\n";
        }
    }

    output.close();

    std::cout << "\nResults written to results.csv\n";

    return 0;
}
