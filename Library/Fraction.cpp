struct Fraction {
    ll f, s;

    Fraction(ll ff, ll ss) {
        f = ff;
        s = ss;
    }

    Fraction operator+(Fraction &other) {
        ll ff = other.f;
        ll ss = other.s;
        ll new_f = f * ss + s * ff;
        ll new_s = s * ss;
        int gg = __gcd(new_f, new_s);
        new_f /= gg;
        new_s /= gg;

        return Fraction(new_f, new_s);

    }

    Fraction operator-(Fraction &other) {
        Fraction f1(f, s);
        Fraction f2(-1 * other.f, other.s);
        return f1 + f2;
    }

    bool operator<(Fraction &other) {
        return f * other.s < s * other.f;
    }

    bool operator==(Fraction &other) {
        return f * other.s == s * other.f;
    }
};
