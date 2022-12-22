/**
 * @file exn.h
 * @author Thomas Roiseux
 * @brief Provides the {@link Exn} class to deal with exceptions.
 * @version 0.1
 * @date 2022-12-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef EXN_H
#define EXN_H

#include <exception>
#include <stdexcept>

/**
 * @brief Exception class.
 * 
 */
class Exn : public std::exception
{
private:
    const char *msg;
public:
    /**
     * @brief Construct a new Exn object.
     * 
     */
    Exn();
    /**
     * @brief Construct a new Exn object.
     * 
     * @param msg The message to display.
     */
    explicit Exn(const char *msg);
    /**
     * @brief Destroy the Exn object.
     * 
     */
    virtual ~Exn();
    /**
     * @brief Get the message.
     * 
     * @return const char* The message.
     */
    virtual const char *what () const noexcept override;
};

#endif // EXN_H 