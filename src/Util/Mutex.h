/*!
 * \file Mutex.h
 *
 * \author czy
 * \date 2023.04.05
 *
 *
 */
#pragma once
#include <mutex>

namespace CUtil{
#define MutexLock(mux)\
 std::unique_lock<std::mutex> lock(mux)
}