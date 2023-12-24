#include "trackmymoves.h"
#include <iostream>

using namespace std;

unsigned int TrackMyMoves::counter_ = 0;

TrackMyMoves::TrackMyMoves(string value)
    : value_(value), id_(counter_++)
{
    cout << id_ << ": constructed with value " << value_ << endl;
}

TrackMyMoves::TrackMyMoves(const TrackMyMoves& rhs)
    : value_(rhs.value_), id_(counter_++)
{
    cout << id_ << ": copy-constructed with value " << value_ << " from " << rhs.id_ << endl;
}

TrackMyMoves::TrackMyMoves(TrackMyMoves&& rhs)
    : value_(rhs.value_), id_(counter_++)
{
    rhs.value_ = string( "moved away, previously ") + value_;
    cout << id_ << ": move-constructed value " << value_ << " from " << rhs.id_ << endl;
}

TrackMyMoves& TrackMyMoves::operator=(const TrackMyMoves& rhs)
{
    value_ = rhs.value_;
    cout << id_ << ": copied value " << value_ << " from " << rhs.id_ << endl;
    return *this;
}

TrackMyMoves& TrackMyMoves::operator=(TrackMyMoves&& rhs)
{
    value_ = rhs.value_;
    rhs.value_ = string( "moved away, previously ") + value_;
    cout << id_ << ": moved value " << value_ << " from " << rhs.id_ << endl;
    return *this;
}

TrackMyMoves::operator string()
{
    return string("TrackMyMoves id=") + to_string(id_) + string(" value=") + value_;
}

