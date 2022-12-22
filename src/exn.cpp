/**
 * @file exn.cpp
 * @author Thomas Roiseux
 * @brief Implements {@link exn.h}.
 * @version 0.1
 * @date 2022-12-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../header/exn.h"

Exn::Exn() : msg("An error occured.")
{
}

Exn::Exn(const char *msg) : msg(msg)
{
}

Exn::~Exn()
{
}

const char *Exn::what() const noexcept
{
    return msg;
}