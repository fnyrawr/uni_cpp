#pragma once

#include <string>

/**
 * @brief The TrackMyMoves class allows to track when objects are
 *        created or assigned by copy or by moving.
 */
class TrackMyMoves {
    std::string value_;
    int id_;
    static unsigned int counter_;
public:

    // normal constructor
    TrackMyMoves(std::string value = "default");

    // copy constructor
    TrackMyMoves(const TrackMyMoves& rhs);

    // move constructor
    TrackMyMoves(TrackMyMoves&& rhs);

    // copy assignment
    TrackMyMoves& operator=(const TrackMyMoves& rhs);

    // move assignment
    TrackMyMoves& operator=(TrackMyMoves&& rhs);

    // conversion to string (for loggin / debugging output)
    operator std::string();
};

