#include "Exceptions.h"
namespace Gaming {
    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
                                                       unsigned height) : DimensionEx(width, height, minWidth,
                                                                                      minHeight) {
        setName("InsufficientDimensionsEx");
    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
        __exp_width = expWidth;
        __exp_height = expHeight;
        __width = width;
        __height = height;
    }

    std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
        ex.__print_args(os);
        return os;
    }

    unsigned DimensionEx::getExpWidth() const {
        return __exp_width;
    }

    unsigned DimensionEx::getExpHeight() const {
        return __exp_height;
    }

    unsigned DimensionEx::getWidth() const {
        return __width;
    }

    unsigned DimensionEx::getHeight() const {
        return __height;
    }

    void GamingException::setName(std::string name) {
        __name = name;
    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        os << getName() << ":\n"
           << "User inputted width: " << this->getWidth() << std::endl
           << "User inputted height: " << this->getHeight() << std::endl
           << "Min width Limit: " << this->getExpWidth() << std::endl
           << "Min height Limit: " << this->getExpHeight() << std::endl;
    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        os << getName() << ":\n"
           << "User inputted width: " << this->getExpWidth() << std::endl
           << "User inputted height: " << this->getExpHeight() << std::endl
           << "Max width Limit: " << this->getWidth() << std::endl
           << "Max height Limit: " << this->getHeight() << std::endl;
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) :
            DimensionEx(width, height, maxWidth, maxHeight) {
        setName("OutOfBoundsEx");
    }
}