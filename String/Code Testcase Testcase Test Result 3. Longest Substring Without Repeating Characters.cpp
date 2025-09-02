#include <array>
#include <string>
#include <algorithm>

int lengthOfLongestSubstring(const std::string& s) {
    const size_t n = s.size();
    if (n <= 1) return static_cast<int>(n);

    std::array<int, 256> freq{}; // counts for all byte values
    freq.fill(0);

    size_t left = 0;
    int best = 0;

    for (size_t right = 0; right < n; ++right) {
        unsigned char cr = static_cast<unsigned char>(s[right]);
        ++freq[cr];

        // shrink until s[right] is unique in the window
        while (freq[cr] > 1) {
            unsigned char cl = static_cast<unsigned char>(s[left]);
            --freq[cl];
            ++left;
        }
        best = std::max(best, static_cast<int>(right - left + 1));
    }
    return best;
}


///2nd 
#include <array>
#include <string>
#include <algorithm>

int lengthOfLongestSubstring(const std::string& s) {
    std::array<int, 256> last;
    last.fill(-1);

    int best = 0;
    int left = 0; // window start (as int to compare with last[])
    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
        unsigned char c = static_cast<unsigned char>(s[static_cast<size_t>(i)]);
        if (last[c] >= left) {
            left = last[c] + 1; // jump left past previous occurrence
        }
        last[c] = i;
        best = std::max(best, i - left + 1);
    }
    return best;
}
