
struct Fact
{
    enum class Type {
        AND,
        OR,
        XOR,
        ANDNOT,
        ORNOT,
        XORNOT,
    };
    enum class Status {
        TRUE,
        FALSE,
        UNDETERMINED
    };
    char _data;
    Type _type;
    Status _status;
};

