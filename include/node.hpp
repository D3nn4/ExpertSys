
struct Fact
{
    enum class Type {
        AND,
        OR,
        XOR,
        ANDNOT,
        // ORNOT,
        // XORNOT,
    };
    char _data;
    Type _type;
};
