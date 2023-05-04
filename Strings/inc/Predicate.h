#ifndef PREDICATE_H
#define PREDICATE_H


class Predicate {
    virtual bool operator()(char c) = 0;
};


class isWhitespace : Predicate {
public:
    bool operator()(char c) override {
        return c == ' ';
    }
};


class isUppercase : Predicate {
public:
    bool operator()(char c) override {
        return c > 64 and c < 91;
    }
};


class isLowercase : Predicate {
public:
    bool operator()(char c) override {
        return c > 96 and c < 123;
    }
};



#endif
