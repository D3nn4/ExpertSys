
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
    char _val;
    Type _type;
};
