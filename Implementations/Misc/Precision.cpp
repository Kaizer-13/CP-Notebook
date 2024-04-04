/***
    https://www.quora.com/What-are-the-differences-between-the-double-and-float-data-types

    Float(32 bits):
        sign bit  : 1 indicates negative, 0 indicates positive or zero
        exponent  : 8 bits
                    x is stored as (x + 127) (example : -10 --> 117)
        precision : 23 bits
                    upto 7-8 significant decimal digits will be accurate

    Double(64 bits):
        sign bit  : 1 indicates negative, 0 indicates positive or zero
        exponent  : 11 bits
                    x is stored as (x + 1023) (example : -5 --> 1018)
        precision : 52 bits
                    upto 15-16 significant decimal digits will be accurate

    Long Double(80 bits):
        sign bit  : 1 indicates negative, 0 indicates positive or zero
        exponent  : 15 bits
                    x is stored as (x + 16383) (example : 3 --> 16386)
        precision : 64 bits
                    upto 19-20 significant decimal digits will be accurate

    If some data type gives x bits precision, it means the first x bits
    of the number will be exact if the number is contained by that data type
***/

