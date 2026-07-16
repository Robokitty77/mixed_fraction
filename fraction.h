
#ifndef FRACTIONS_FRACTION_H
#define FRACTIONS_FRACTION_H


#include <string>
#include <stdexcept>

class fraction {
private:
	unsigned int numerator, denominator, whole;
	bool isPos;
public:
	explicit fraction() : numerator(0), denominator(1), whole(0), isPos(true) {};
	fraction(const long int num, const long int denom, const long int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}

		this->isPos = !(wh < 0 || (num < 0 ^ denom < 0));
		this->numerator = abs(num);
		this->denominator = abs(denom);
		this->whole = abs(wh);
	}
	fraction(const int num, const int denom, const int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}

		this->isPos = !(wh < 0 || (num < 0 ^ denom < 0));
		this->numerator = abs(num);
		this->denominator = abs(denom);
		this->whole = abs(wh);
	}
	fraction(const unsigned int num, const unsigned int denom, const unsigned int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		this->isPos = true;
		this->numerator = num;
		this->denominator = denom;
		this->whole = wh;
	}
	explicit fraction(const long int wh) {
		this->whole = abs(wh);
		this->numerator = 0;
		this->denominator = 1;
		this->isPos = wh >= 0;
	}
	explicit fraction(const int wh) {
		this->whole = abs(wh);
		this->numerator = 0;
		this->denominator = 1;
		this->isPos = wh >= 0;
	}
	explicit fraction(const unsigned int wh) {
		this->whole = wh;
		this->numerator = 0;
		this->denominator = 1;
		this->isPos = true;
	}
	fraction(const fraction &other) {
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		this->whole = other.whole;
		this->isPos = other.isPos;
	}

	~fraction() = default;

	[[nodiscard]] std::string toString() const {
		if (this->numerator == 0) {
			return (this->isPos? "" : "-") +
				std::to_string(this->whole);
		}
		if (this->whole == 0) {
			return (this->isPos? "" : "-") +
				std::to_string(this->numerator) + "/" +
				std::to_string(this->denominator);
		}
		return (this->isPos? "" : "-") +
			std::to_string(this->whole) + " " +
			std::to_string(this->numerator) + "/" +
			std::to_string(this->denominator);
	}

	void setWhole(long int wh) {
		this->whole = wh;
		if (wh < 0) {
			this->isPos = false;
		}
		else {
			this->isPos = true;
		}
	}
	void setNumerator(long int num) {
		this->numerator = num;
		if (num < 0) {
			this->isPos = false;
		}
		else {
			this->isPos = true;
		}
	}
	void setDenominator(long int denom) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(this->numerator) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		this->denominator = denom;
		if (denom < 0) {
			this->isPos = false;
		}
		else {
			this->isPos = true;
		}
	}

	bool balanceDenominatorAs(long int balancenum) {
		if (balancenum == 0) {
			throw std::invalid_argument(std::to_string(this->numerator) + " / " + std::to_string(balancenum) +
	" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		if (this->denominator == balancenum) {
			return true;
		}
		this->isPos = balancenum > 0;
		balancenum = abs(balancenum);
		if (this->numerator == 0) {
			this->denominator = balancenum;
			return true;
		}
		if (balancenum % this->denominator == 0) {
			this->numerator *= balancenum / this->denominator;
			this->denominator = balancenum;
			return true;
		}
		if (this->denominator % balancenum == 0 && this->numerator % (this->denominator / balancenum) == 0) {
			this->numerator /= this->denominator / balancenum;
			this->denominator = balancenum;
			return true;
		}
		fraction bsearch = *this;
		bsearch.denominator = balancenum;
		fraction lesserfrac = *this;
		lesserfrac.denominator = balancenum;
		fraction greaterfrac = *this;
		greaterfrac.denominator = balancenum;

		unsigned int upper, lower;
		if (this->denominator > balancenum) {
			upper = this->numerator;
			lower = this->numerator /
			((this->denominator > balancenum?
				this->denominator / balancenum :
				balancenum / this->denominator)
			+ 1);
		}
		else {
			lower = this->numerator;
			upper = this->numerator *
			((this->denominator > balancenum?
				this->denominator / balancenum :
				balancenum / this->denominator)
			+ 1);
		}

		do {
			lesserfrac.numerator = bsearch.numerator - 1;
			greaterfrac.numerator = bsearch.numerator + 1;
			if ((lesserfrac - *this).asPositive() > (bsearch - *this).asPositive()
				&& (greaterfrac - *this).asPositive() > (bsearch - *this).asPositive()) {
					break;
			}
			if ((lesserfrac - *this).asPositive() < (greaterfrac - *this).asPositive()) {
				upper = bsearch.numerator;
				bsearch = (bsearch.numerator + lower) / 2;
			}
			else {
				lower = bsearch.numerator;
				bsearch = (bsearch.numerator + upper) / 2;
			}
		} while (upper > lower);
		this->numerator = bsearch.numerator;
		return false;
	}
	bool balanceDenominatorAs(unsigned int balancenum) {
		if (balancenum == 0) {
			throw std::invalid_argument(std::to_string(this->numerator) + " / " + std::to_string(balancenum) +
	" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		if (this->denominator == balancenum) {
			return true;
		}
		if (this->numerator == 0) {
			this->denominator = balancenum;
			return true;
		}
		if (balancenum % this->denominator == 0) {
			this->numerator *= balancenum / this->denominator;
			this->denominator = balancenum;
			return true;
		}
		if (this->denominator % balancenum == 0 && this->numerator % (this->denominator / balancenum) == 0) {
			this->numerator /= this->denominator / balancenum;
			this->denominator = balancenum;
			return true;
		}
		fraction bsearch = *this;
		bsearch.denominator = balancenum;
		fraction lesserfrac = *this;
		lesserfrac.denominator = balancenum;
		fraction greaterfrac = *this;
		greaterfrac.denominator = balancenum;

		unsigned int upper, lower;
		if (this->denominator > balancenum) {
			upper = balancenum;
			lower = this->numerator /
			((this->denominator > balancenum?
				this->denominator / balancenum :
				balancenum / this->denominator)
			+ 1);
		}
		else {
			lower = balancenum;
			upper = this->numerator *
			((this->denominator > balancenum?
				this->denominator / balancenum :
				balancenum / this->denominator)
			+ 1);
		}

		do {
			lesserfrac.numerator = bsearch.numerator - 1;
			greaterfrac.numerator = bsearch.numerator + 1;
			if ((lesserfrac - *this).asPositive() > (bsearch - *this).asPositive()
				&& (greaterfrac - *this).asPositive() > (bsearch - *this).asPositive()) {
					break;
			}
			if ((lesserfrac - *this).asPositive() < (greaterfrac - *this).asPositive()) {
				upper = bsearch.numerator;
				bsearch = (bsearch.numerator + lower) / 2;
			}
			else {
				lower = bsearch.numerator;
				bsearch = (bsearch.numerator + upper) / 2;
			}
		} while (upper > lower);
		this->numerator = bsearch.numerator;
		return false;
	}
	bool balanceNumeratorAs(long int balancenum) {
		if (this->numerator == balancenum) {
			return true;
		}
		if ((balancenum <= (this->whole * this->denominator) + this->numerator)
			&& this->isPos == balancenum > 0) {
			if (this->numerator % this->denominator == balancenum % this->denominator) {
				if (balancenum > this->numerator) {
					this->whole -= (balancenum - this->numerator) / this->denominator;
				}
				else {
					this->whole += (this->numerator - balancenum) / this->denominator;
				}
				this->numerator = balancenum;
				return true;
			}
			if (balancenum > this->numerator) {
				this->whole -= (balancenum - this->numerator) / this->denominator + 1;
			}
			else {
				this->whole += (this->numerator - balancenum) / this->denominator;
			}
			return false;
		}
		this->isPos = balancenum > 0;
		this->numerator = abs(balancenum);
		this->whole = 0;
		return false;
	}
	bool balanceNumeratorAs(unsigned int balancenum) {
		if (this->numerator == balancenum) {
			return true;
		}
		if (balancenum <= (this->whole * this->denominator) + this->numerator) {
			if (this->numerator % this->denominator == balancenum % this->denominator) {
				if (balancenum > this->numerator) {
					this->whole -= (balancenum - this->numerator) / this->denominator;
				}
				else {
					this->whole += (this->numerator - balancenum) / this->denominator;
				}
				this->numerator = balancenum;
				return true;
			}
			if (balancenum > this->numerator) {
				this->whole -= (balancenum - this->numerator) / this->denominator + 1;
			}
			else {
				this->whole += (this->numerator - balancenum) / this->denominator;
			}
			return false;
	}
		this->numerator = balancenum;
		this->whole = 0;
		return false;
	}
	bool balanceWholeAs(long int balancenum) {
		if (this->whole == balancenum) {
			return true;
		}
		if ((this->denominator * abs(balancenum) <= (this->whole * this->denominator) + this->numerator)
			&& (this->isPos == balancenum > 0)) {
			if (this->whole < balancenum) {
				this->numerator -= (balancenum - this->whole) * this->denominator;
			}
			else {
				this->numerator += (this->whole - balancenum) * this->denominator;
			}
			this->whole = abs(balancenum);
			return true;
			}
		this->isPos = balancenum > 0;
		this->whole = abs(balancenum);
		this->numerator = 0;
		return false;
	}
	bool balanceWholeAs(unsigned int balancenum) {
		if (this->whole == balancenum) {
			return true;
		}
		if (this->denominator * balancenum <= (this->whole * this->denominator) + this->numerator) {
			if (this->whole < balancenum) {
				this->numerator -= (balancenum - this->whole) * this->denominator;
			}
			else {
				this->numerator += (this->whole - balancenum) * this->denominator;
			}
			this->whole = balancenum;
			return true;
		}
		this->whole = balancenum;
		this->numerator = 0;
		return false;
	}

	[[nodiscard]] long int getDenominator() const {
		if (this->isPos) {
			return (long)this->denominator;
		}
		return (long)this->denominator * -1;
	}
	[[nodiscard]] long int getNumerator() const {
		if (this->isPos) {
			return (long)this->numerator;
		}
		return (long)this->numerator * -1;
	}
	[[nodiscard]] long int getWhole() const {
		if (this->isPos) {
			return (long)this->whole;
		}
		return (long)this->whole * -1;
	}
	[[nodiscard]] long int getProperNumerator() const {
		if (this->isPos) {
			return (long)(this->numerator % this->denominator);
		}
		return (long)(this->numerator % this->denominator) * -1;
	}
	[[nodiscard]] long int getImproperNumerator() const {
		if (this->isPos) {
			return (long)(this->numerator) + (long)(this->whole * this->denominator);
		}
		return (long)(this->numerator) + (long)(this->whole * this->denominator) * -1;
	}

	[[nodiscard]] long int floored() const {
		return (long)(this->whole) + (long)(this->numerator / this->denominator);
	}
	[[nodiscard]] long int rounded() const {
		return ((this->numerator % this->denominator) * 2 >= this->denominator)? this->ceilinged() : this->floored();
	}
	[[nodiscard]] long int ceilinged() const {
		return this->floored() + (((this->numerator % this->denominator) == 0)? 0: 1);
	}

	void floor() {
		this->numerator -= (this->numerator % this->denominator);
	}
	void round() {
		if (this->numerator % this->denominator == 0) {
			return;
		}

		if ((this->numerator % this->denominator) * 2 >= this->denominator) {
			this->numerator += this->denominator;
		}

		this->numerator -= (this->numerator % this->denominator);
	}
	void ceiling() {
		if (this->numerator % this->denominator == 0) {
			return;
		}
		this->numerator -= (this->numerator % this->denominator);
		this->numerator += this->denominator;
	}

	[[nodiscard]] bool isPositive() const {
		return this->isPos;
	}
	[[nodiscard]] bool isNegative() const {
		return !this->isPos;
	}
	[[nodiscard]] bool isReduced() const {
		if (this->numerator == 0 || this->numerator == 1) {
			return true;
		}
		for (unsigned int i = 2; i <= ((this->numerator < this->denominator)? this->numerator : this->denominator)/2; i++) {
			if (this->numerator % i == 0 && this->denominator % i == 0) {
				return false;
			}
		}
		return true;
	}
	[[nodiscard]] bool isProper() const {
		return this->numerator < this->denominator;
	} 
	[[nodiscard]] bool isImproper() const {
		return this->numerator > this->denominator; 
	}
	
	[[nodiscard]] fraction asPositive() const {
		fraction newfrac = *this;
		newfrac.isPos = true;
		return newfrac;
	}
	[[nodiscard]] fraction asNegative() const {
		fraction newfrac = *this;
		newfrac.isPos = false;
		return newfrac;
	}
	[[nodiscard]] fraction asOpposite() const {
		fraction newfrac = *this;
		newfrac.isPos = !newfrac.isPos;
		return newfrac;
	}
	[[nodiscard]] fraction asReduced() const {
		fraction newfrac = *this;
		newfrac.reduce();
		return newfrac;
	}
	[[nodiscard]] fraction asProper() const {
		fraction newfrac = *this;
		newfrac.proper();
		return newfrac;
	}
	[[nodiscard]] fraction asImproper() const {
		fraction newfrac = *this;
		newfrac.improper();
		return newfrac;
	}
	[[nodiscard]] fraction asInverted() const {
		fraction newfrac = *this;
		newfrac.invert();
		return newfrac;
	}

	void positive() {
		this->isPos = true;
	}
	void negative() {
		this->isPos = false;
	}
	void opposite() {
		this->isPos = !this->isPos;
	}
	void reduce() {
		if (this->numerator == 0 || this->numerator == 1) {
			return;
		}
		if (this->numerator % this->denominator == 0) {
			this->numerator /= this->denominator;
			this->denominator = 1;
			return;
		}
		if (this->denominator % this->numerator == 0) {
			this->denominator /= this->numerator;
			this->numerator = 1;
			return;
		}
		unsigned int i = this->numerator < this->denominator? this->numerator : this->denominator;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2 ; i--) {
			if (this->numerator % i == 0 && this->denominator % i == 0) {
				this->numerator /= i;
				this->denominator /= i;
			}
			if (this->numerator == 1 || this->denominator == 1) {
				return;
			}
		}
	}
	void proper() {
		this->whole += this->numerator / this->denominator;
		this->numerator %= this->denominator;
	}
	void improper() {
		this->numerator += this->denominator * this->whole;
		this->whole = 0;
	}
	void invert() {
		unsigned long long int swapper = this->denominator * this->whole;
		swapper += this->numerator;
		this->whole = this->denominator / swapper;
		this->numerator = this->denominator % swapper;
		this->denominator = swapper;
	}

	fraction& operator=(const int& copynum) {
		this->numerator = 0;
		this->whole = abs(copynum);
		this->isPos = copynum >= 0;
		return *this;
	}
	fraction& operator=(const unsigned int& copynum) {
		this->numerator = 0;
		this->whole = copynum;
		this->isPos = true;
		return *this;
	}
	fraction& operator=(const fraction& copynum) {
		this->numerator = copynum.numerator;
		this->denominator = copynum.denominator;
		this->whole = copynum.whole;
		this->isPos = copynum.isPos;
		return *this;
	}

	fraction operator++() {
		if (this->isPos) {
			if (this->whole != 0) {
				this->whole++;
			}
			else {
				this->numerator += this->denominator;
			}
		}
		else {
			if (this->whole == 0 && this->numerator < this->denominator) {
				this->numerator = this->denominator - this->numerator;
				this->isPos = true;
			}
			else if (this->numerator < this->denominator) {
				this->whole--;
			}
			else {
				this->numerator -= this->denominator;
			}
		}
		return * this;
	}
	fraction operator++(int) {
		fraction fractioncopy = *this;
		++*this;
		return fractioncopy;
	}

	fraction operator--() {
		if (!this->isPos) {
			if (this->whole != 0) {
				this->whole++;
			}
			else {
				this->numerator += this->denominator;
			}
		}
		else {
			if (this->whole == 0 && this->numerator < this->denominator) {
				this->numerator = this->denominator - this->numerator;
				this->isPos = false;
			}
			else if (this->numerator < this->denominator) {
				this->whole--;
			}
			else {
				this->numerator -= this->denominator;
			}
		}
		return * this;
	}
	fraction operator--(int) {
		fraction fractioncopy = *this;
		--*this;
		return fractioncopy;
	}

	fraction operator+=(const long int& addnum) {
		if (addnum < 0) {
			return *this -= (addnum * -1);
		}
		if (this->isPos) {
			if (this->whole == 0) {
				this->numerator += (addnum * this->denominator);
				return * this;
			}
			this->whole += addnum;
			return * this;
		}

		if (this->whole == 0) {
			if (addnum * this->denominator < this->numerator) {
				this->numerator -= (addnum * this->denominator);
				return * this;
			}
			this->isPos = true;
			this->numerator = (addnum * this->denominator) - this->numerator;
			return * this;
		}

		if (this->whole >= addnum) {
			this->whole -= addnum;
			this->isPos = this->whole == 0;
			return * this;
		}

		if (this->numerator >= addnum * this->denominator) {
			this->numerator -= (addnum * this->denominator);
			return * this;
		}

		long int copynum = addnum;
		copynum -= (long)this->whole;
		this->whole = 0;

		return *this += copynum;
	}
	friend long int operator+=(long int integer, const fraction& addnum) {
		long int * copynum = &integer;
		*copynum += addnum.floored();
		return *copynum;
	}
	fraction operator+(const long int& addnum) const {
		fraction result(*this);
		result += addnum;
		return result;
	}
	friend fraction operator+(const long int& integer, const fraction& addnum) {
		fraction fractioncopy(addnum);
		fractioncopy += integer;
		return fractioncopy;
	}
	fraction operator+=(const unsigned int& addnum) {
		if (this->isPos) {
			if (this->whole == 0) {
				this->numerator += (addnum * this->denominator);
				return * this;
			}
			this->whole += addnum;
			return * this;
		}

		if (this->whole == 0) {
			if (addnum * this->denominator < this->numerator) {
				this->numerator -= (addnum * this->denominator);
				return * this;
			}
			this->isPos = true;
			this->numerator = (addnum * this->denominator) - this->numerator;
			return * this;
		}

		if (this->whole >= addnum) {
			this->whole -= addnum;
			this->isPos = this->whole == 0;
			return * this;
		}

		if (this->numerator >= addnum * this->denominator) {
			this->numerator -= (addnum * this->denominator);
			return * this;
		}

		unsigned int copynum = addnum;
		copynum -= this->whole;
		this->whole = 0;

		return * this += copynum;
	}
	friend unsigned int operator+=(unsigned int integer, const fraction& addnum) {
		unsigned int * copynum = &integer;
		*copynum += addnum.floored();
		return *copynum;
	}
	fraction operator+(const unsigned int& addnum) const {
		fraction result(*this);
		result += addnum;
		return result;
	}
	friend fraction operator+(unsigned int integer, const fraction& addnum) {
		fraction fractioncopy(addnum);
		fractioncopy += integer;
		return fractioncopy;
	}
	fraction operator+=(const fraction& addnum) {
		fraction fractioncopy(addnum);
		if (!addnum.isPos) {
			fractioncopy.isPos = true;
			return *this -= fractioncopy;
		}
		LCD(this, &fractioncopy);

		if (this->isPos) {
			this->whole += fractioncopy.whole;
			this->numerator += fractioncopy.numerator;
			return * this;
		}

		fractioncopy.proper();
		if (this->whole != 0 && fractioncopy.whole != 0) {
			if (this->whole < fractioncopy.whole) {
				fractioncopy.whole -= this->whole;
				this->whole = 0;
			}
			else {
				this->whole -= fractioncopy.whole;
				fractioncopy.whole = 0;
			}
			if (this->whole == 0 && this->numerator == 0) {
				this->isPos = true;
				return *this += fractioncopy;
			}
		}

		fractioncopy.improper();
		if (this->numerator < fractioncopy.numerator) {
			fractioncopy.numerator -= this->numerator;
			this->numerator = 0;
		}
		else {
			this->numerator -= fractioncopy.numerator;
			fractioncopy.numerator = 0;
		}

		if (this->numerator == 0) {
			this->isPos = true;
			this->numerator = fractioncopy.numerator;
		}
		this->reduce();
		return * this;
	}
	fraction operator+(const fraction& addnum) const {
		fraction result(*this);
		result += addnum;
		return result;
	}

	fraction operator-=(const long int& subnum) {
		if (subnum < 0) {
			return * this += (subnum * -1);
		}
		if (!this->isPos) {
			if (this->whole == 0) {
				this->numerator += (subnum * this->denominator);
				return * this;
			}
			this->whole += subnum;
			return * this;
		}

		if (this->whole == 0) {
			if (subnum * this->denominator < this->numerator) {
				this->numerator -= (subnum * this->denominator);
				return * this;
			}
			this->isPos = false;
			this->numerator = (subnum * this->denominator) - this->numerator;
			return * this;
		}

		if (this->whole >= subnum) {
			this->whole -= subnum;
			return * this;
		}

		if (this->numerator >= subnum * this->denominator) {
			this->numerator -= (subnum * this->denominator);
			return * this;
		}

		long int copynum = subnum;
		copynum -= (long)this->whole;
		this->whole = 0;

		return * this -= copynum;
	}
	friend long int operator-=(long int integer, const fraction& subnum) {
		if (!subnum.isPos) {
			return integer += subnum.asPositive();
		}
		if (integer >=0 && integer < subnum) {
			return integer -= subnum.floored();
		}
		return integer -= subnum.ceilinged();
	}
	fraction operator-(const long int& subnum) const {
		fraction result(*this);
		result -= subnum;
		return result;
	}
	friend fraction operator-(const long int integer, const fraction& subnum) {
		if (!subnum.isPos) {
			return integer - subnum.asPositive();
		}
		fraction result(integer);
		result -= subnum;
		return result;
	}
	fraction operator-=(const unsigned int& subnum) {
		if (!this->isPos) {
			if (this->whole == 0) {
				this->numerator += (subnum * this->denominator);
				return * this;
			}
			this->whole += subnum;
			return * this;
		}

		if (this->whole == 0) {
			if (subnum * this->denominator < this->numerator) {
				this->numerator -= (subnum * this->denominator);
				return * this;
			}
			this->isPos = false;
			this->numerator = (subnum * this->denominator) - this->numerator;
			return * this;
		}

		if (this->whole >= subnum) {
			this->whole -= subnum;
			return * this;
		}

		if (this->numerator >= subnum * this->denominator) {
			this->numerator -= (subnum * this->denominator);
			return * this;
		}

		unsigned int copynum = subnum;
		copynum -= this->whole;
		this->whole = 0;

		return * this -= copynum;
	}
	friend unsigned int operator-=(unsigned int integer, const fraction& subnum) {
		if (!subnum.isPos) {
			return integer += subnum.asPositive();
		}
		if (integer < subnum) {
			return integer -= subnum.floored();
		}
		integer = 0;
		return integer;
	}
	fraction operator-(const unsigned int& subnum) const {
		fraction result(*this);
		result -= subnum;
		return result;
	}
	friend fraction operator-(const unsigned int integer, const fraction& subnum) {
		fraction result(integer);
		result -= subnum;
		return result;
	}
	fraction operator-=(const fraction& subnum) {
		fraction fractioncopy(subnum);
		if (subnum.isPos) {
			fractioncopy.isPos = true;
			return *this += fractioncopy;
		}
		LCD(this, &fractioncopy);

		if (!this->isPos) {
			this->whole += fractioncopy.whole;
			this->numerator += fractioncopy.numerator;
			return * this;
		}

		fractioncopy.proper();
		if (this->whole != 0 && fractioncopy.whole != 0) {
			if (this->whole < fractioncopy.whole) {
				fractioncopy.whole -= this->whole;
				this->whole = 0;
			}
			else {
				this->whole -= fractioncopy.whole;
				fractioncopy.whole = 0;
			}
			if (this->whole == 0 && this->numerator == 0) {
				this->isPos = false;
				return *this += fractioncopy;
			}
		}

		fractioncopy.improper();
		if (this->numerator < fractioncopy.numerator) {
			fractioncopy.numerator -= this->numerator;
			this->numerator = 0;
		}
		else {
			this->numerator -= fractioncopy.numerator;
			fractioncopy.numerator = 0;
		}

		if (this->numerator == 0) {
			this->isPos = false;
			this->numerator = fractioncopy.numerator;
		}
		this->reduce();
		return * this;
	}
	fraction operator-(const fraction& subnum) const {
		fraction result(*this);
		result -= subnum;
		return result;
	}

	fraction operator*=(const long int& multnum) {
		if (multnum < 0) {
			this->isPos = !this->isPos;
		}
		int copynum = abs(multnum);
		this->whole *= copynum;
		for (int i = 1; i <= (copynum / 2); i++) {
			if (copynum % i == 0) {
				if (this->denominator % (copynum / i) == 0) {
					this->denominator /= (copynum / i);
					copynum /= i;
				}
			}
		}
		this->numerator *= copynum;
		return * this;
	}
	friend long int operator*=(long int integer, const fraction& multnum) {
		return (multnum * integer).floored();
	}
	fraction operator*(const long int& multnum) const {
		fraction result(*this);
		result *= multnum;
		return result;
	}
	friend fraction operator*(const long int integer, const fraction& multnum) {
		return multnum * integer;
	}
	fraction operator*=(const unsigned int& multnum) {
		unsigned int copynum = multnum;
		this->whole *= copynum;
		for (int i = 1; i <= (copynum / 2); i++) {
			if (copynum % i == 0) {
				if (this->denominator % (copynum / i) == 0) {
					this->denominator /= (copynum / i);
					copynum /= i;
				}
			}
		}
		this->numerator *= copynum;
		return * this;
	}
	friend unsigned int operator*=(unsigned int integer, const fraction& multnum) {
		fraction fractioncopy(multnum);
		fractioncopy *= integer;
		integer = fractioncopy.floored();
		return integer;
	}
	fraction operator*(const unsigned int& multnum) const {
		fraction result(*this);
		result *= multnum;
		return result;
	}
	friend fraction operator*(const unsigned int integer, const fraction& multnum) {
		fraction fractioncopy(multnum);
		fractioncopy *= integer;
		return fractioncopy;
	}
	fraction operator*=(const fraction& multnum) {
		fraction copynum = multnum;
		if (this->whole != 0) {
			unsigned int wholestorage = this->whole;
			this->whole = 0;
			return (wholestorage * copynum) + (*this * copynum);
		}
		if (copynum.whole != 0) {
			unsigned int wholestorage = copynum.whole;
			copynum.whole = 0;
			return (*this * wholestorage) + (*this * copynum);
		}

		if (this->numerator % copynum.denominator == 0) {
			this->numerator /= copynum.denominator;
			copynum.denominator = 1;
		}
		else if (copynum.denominator % this->numerator == 0) {
			copynum.denominator /= this->numerator;
			this->numerator = 1;
		}
		else {
			unsigned int i1 = (this->numerator < copynum.denominator? this->numerator : copynum.denominator);
			i1 /= (i1 % 2 == 0? 2 : 3);
			for (; i1 >= 2; i1--) {
				if (this->numerator % i1 == 0 && copynum.denominator % i1 == 0) {
					this->numerator /= i1;
					copynum.denominator /= i1;
				}
			}
		}

		if (copynum.numerator % this->denominator == 0) {
			copynum.numerator /= this->denominator;
			this->denominator = 1;
		}
		else if (this->denominator % copynum.numerator == 0) {
			this->denominator /= copynum.numerator;
			copynum.numerator = 1;
		}
		else {
			unsigned int i2 = (copynum.numerator < this->denominator? copynum.numerator : this->denominator);
			i2 /= (i2 % 2 == 0? 2 : 3);
			for (; i2 >= 2; i2--) {
				if (copynum.numerator % i2 == 0 && this->denominator % i2 == 0) {
					copynum.numerator /= i2;
					this->denominator /= i2;
				}
			}
		}

		this->reduce();
		copynum.reduce();

		this->numerator *= copynum.numerator;
		this->denominator *= copynum.denominator;

		if (!multnum.isPos) {
			this->isPos = !this->isPos;
		}
		return * this;
	}
	fraction operator*(const fraction& multnum) const {
		fraction result(*this);
		result *= multnum;
		return result;
	}

	fraction operator/=(const long int& divnum) {
		this->improper();
		if (divnum < 0) {
			this->isPos = !this->isPos;
		}
		int copynum = divnum;
		for (int i = 1; i <= (copynum / 2); i++) {
			if (copynum % i == 0) {
				if (this->numerator % (copynum / i) == 0) {
					this->numerator /= (copynum / i);
					copynum /= i;
				}
			}
		}
		this->denominator *= copynum;
		return * this;
	}
	friend long int operator/=(long int integer, const fraction& divnum) {
		bool mismatch = integer > 0 != divnum.isPos;
		integer = abs(integer);
		fraction fractioncopy(divnum);
		fractioncopy.improper();
		for (int i = 1; i <= (integer / 2); i++) {
			if (integer % i == 0) {
				if (fractioncopy.numerator % (integer / i) == 0) {
					fractioncopy.numerator /= (integer / i);
					integer /= i;
				}
			}
		}
		fractioncopy.denominator *= integer;
		integer = fractioncopy.floored();
		if (mismatch) {
			integer *= -1;
		}
		return integer;
	}
	fraction operator/(const long int& divnum) const {
		fraction result(*this);
		result /= divnum;
		return result;
	}
	friend fraction operator/(const long int integer, const fraction& divnum) {
		fraction result(integer);
		result /= divnum;
		return result;
	}
	fraction operator/=(const unsigned int& divnum) {
		this->improper();
		unsigned int copynum = divnum;
		for (int i = 1; i <= (copynum / 2); i++) {
			if (copynum % i == 0) {
				if (this->numerator % (copynum / i) == 0) {
					this->numerator /= (copynum / i);
					copynum /= i;
				}
			}
		}
		this->denominator *= copynum;
		return * this;
	}
	friend unsigned int operator/=(unsigned int integer, const fraction& divnum) {
		fraction fractioncopy(divnum);
		unsigned int copynum(integer);
		fractioncopy.improper();
		for (int i = 1; i <= (integer / 2); i++) {
			if (integer % i == 0) {
				if (fractioncopy.numerator % (integer / i) == 0) {
					fractioncopy.numerator /= (integer / i);
					integer /= i;
				}
			}
		}
		fractioncopy.denominator *= integer;
		copynum = fractioncopy.floored();
		return copynum;
	}
	fraction operator/(const unsigned int& divnum) const {
		fraction result(*this);
		result /= divnum;
		return result;
	}
	friend fraction operator/(const unsigned int integer, const fraction& divnum) {
		fraction result(integer);
		result /= divnum;
		return result;
	}
	fraction operator/=(const fraction& divnum) {
		// impnum, or improper numerator, is *(this)'s numerator in improper form
		// it has been given a size of 64 bits to eliminate the risk of overflow on declaration
		unsigned long long int impnum = this->denominator * this->whole;
		// it is still possible for this addition to overflow, though
		impnum += this->numerator;
		// impdenom, or improper denominator, follows the same logic but for divnum
		// it's the "denominator" even though it uses the same formula
		// to model fraction division being an inversion + multiplication
		unsigned long long int impdenom = divnum.denominator * divnum.whole;
		impdenom += divnum.numerator;
		// divnum's denominator needs to be editable, it is the numerator of the inverted fraction
		unsigned int numeratorcopy = divnum.denominator;
		// impnum has already taken into account the value of this' whole portion
		this->whole = 0;

		// from here, the logic is nearly identical to that seen in fraction *= fraction with whole values of 0
		// impnum replaces this->numerator
		// this->denominator gets to stay
		// numeratorcopy replaces divnum.numerator
		// impdenom replaces divnum.denominator

		// this is an attempt at cross-reducing the fractional values before multiplying anything
		// doing this minimizes the value of the numbers that get multiplied together in the end
		// prime numbers will drag out the runtime, currently
		// first, catch the case of one numerator being able to evenly divide the denominator or vice versa
		if (impnum != 0 && impnum != 1) {
			if (impnum % impdenom == 0) {
				impnum /= impdenom;
				impdenom = 1;
			}
			else if (impdenom != 1 && impdenom % impnum == 0) {
				impdenom /= impnum;
				impnum = 1;
			}
			else {
				// most cases will end up here, where the numbers are divided by any common factors
				// the largest value that could conceivably divide both values cannot be larger than the smallest value
				// in fact, if the smallest value is even, its largest significant factor is half of it
				// if it's odd, it isn't divisible by two, so then divide by 3 instead to minimize loop iterations
				unsigned int i1 = (impnum < impdenom? impnum : impdenom);
				i1 /= (i1 % 2 == 0? 2 : 3);
				for (; i1 >= 2; i1--) {
					// if the loop counter finds a common factor of both impnum and impdenom, divide them both
					if (impnum % i1 == 0 && impdenom % i1 == 0) {
						impnum /= i1;
						impdenom /= i1;
					}
				}
			}
		}

		// this is a repeat of the above logic but with the other cross pairing of numerator and denominator
		if (numeratorcopy != 0 && numeratorcopy != 1) {
			if (numeratorcopy % this->denominator == 0) {
				numeratorcopy /= this->denominator;
				this->denominator = 1;
			}
			else if (this->denominator % numeratorcopy == 0) {
				this->denominator /= numeratorcopy;
				numeratorcopy = 1;
			}
			else {
				unsigned int i2 = (numeratorcopy < this->denominator? numeratorcopy : this->denominator);
				i2 /= (i2 % 2 == 0? 2 : 3);
				for (; i2 >= 2; i2--) {
					if (numeratorcopy % i2 == 0 && this->denominator % i2 == 0) {
						numeratorcopy /= i2;
						this->denominator /= i2;
					}
				}
			}
		}
		// end repeat of logic

		// below is essentially the .reduce() method twice, but with slightly different logic
		// to work on a discrete pair of variables and not an object
		if (impnum != 0 && impnum != 1) {
			if (impnum % this->denominator == 0) {
				impnum /= this->denominator;
				this->denominator = 1;
			}
			else if (this->denominator % impnum == 0) {
				this->denominator /= impnum;
				impnum = 1;
			}
			else {
				unsigned int i3 = (impnum < this->denominator? impnum : this->denominator);
				i3 /= (i3 % 2 == 0? 2 : 3);
				for (; i3 >= 2 ; i3--) {
					if (impnum % i3 == 0 && this->denominator % i3 == 0) {
						impnum /= i3;
						this->denominator /= i3;
					}
					if (impnum == 1 || this->denominator == 1) {
						break;
					}
				}
			}
		}

		if (numeratorcopy != 0 && numeratorcopy != 1) {
			if (numeratorcopy % impdenom == 0) {
				numeratorcopy /= impdenom;
				impdenom = 1;
			}
			else if (impdenom % numeratorcopy == 0) {
				impdenom /= numeratorcopy;
				numeratorcopy = 1;
			}
			else {
				unsigned int i4 = (numeratorcopy < impdenom? numeratorcopy : impdenom);
				i4 /= (i4 % 2 == 0? 2 : 3);
				for (; i4 >= 2 ; i4--) {
					if (numeratorcopy % i4 == 0 && impdenom % i4 == 0) {
						numeratorcopy /= i4;
						impdenom /= i4;
					}
					if (numeratorcopy == 1 || impdenom == 1) {
						break;
					}
				}
			}
		}

		// after the above, the numbers are as low as conceivably possible
		// in the future, this is where a check for overflow will go and an error possibly thrown
		this->numerator = impnum * numeratorcopy;
		this->denominator *= impdenom;
		if (!divnum.isPos) {
			this->isPos = !this->isPos;
		}
		return * this;
	}
	fraction operator/(const fraction& divnum) const {
		fraction result(*this);
		result /= divnum;
		return result;
	}

	fraction operator%=(const long int& modnum) {
		this->improper();
		this->numerator %= (modnum * this->denominator);
		return * this;
	}
	friend long int operator%=(long int integer, const fraction& modnum) {
		integer = abs(integer);
		integer *= (long)modnum.denominator;
		integer %= (long)(modnum.numerator + (modnum.denominator * modnum.whole));
		integer /= (long)modnum.denominator;
		return integer;
	}
	fraction operator%(const long int& modnum) const {
		fraction result(*this);
		result %= modnum;
		return result;
	}
	friend fraction operator%(const long int integer, const fraction& modnum) {
		fraction result(integer);
		result %= modnum;
		return result;
	}
	fraction operator%=(const unsigned int& modnum) {
		this->improper();
		this->numerator %= (modnum * this->denominator);
		return * this;
	}
	friend unsigned int operator%=(unsigned int integer, const fraction& modnum) {
		integer *= (long)modnum.denominator;
		integer %= (long)(modnum.numerator + (modnum.denominator * modnum.whole));
		integer /= (long)modnum.denominator;
		return integer;
	}
	fraction operator%(const unsigned int& modnum) const {
		fraction result(*this);
		result %= modnum;
		return result;
	}
	friend fraction operator%(const unsigned int integer, const fraction& modnum) {
		fraction result(integer);
		result %= modnum;
		return result;
	}
	fraction operator%=(const fraction& modnum) {
		fraction fractioncopy = *this / modnum;
		fractioncopy.floor();
		fractioncopy *= modnum;
		*this -= fractioncopy;
		return * this;
	}
	fraction operator%(const fraction& modnum) const {
		fraction result(*this);
		result %= modnum;
		return result;
	}

	bool operator<(const long int& compnum) const {
		if (!this->isPos && compnum > 0) {
			return true;
		}
		if (this->isPos && compnum < 0) {
			return false;
		}
		return (this->numerator + this->whole * this->denominator < compnum * this->denominator)
				^ (!this->isPos && compnum < 0);
	}
	friend bool operator<(const long int integer, const fraction& compnum) {
		if (compnum.isPos && integer < 0) {
			return true;
		}
		if (!compnum.isPos && integer > 0) {
			return false;
		}
		return (integer * compnum.denominator < compnum.numerator + (compnum.whole * compnum.denominator))
				^ (!compnum.isPos && integer < 0);
	}
	bool operator<(const unsigned int& compnum) const {
		if (!this->isPos) {
			return true;
		}
		return this->numerator + this->whole * this->denominator < compnum * this->denominator;
	}
	friend bool operator<(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return false;
		}
		return integer * compnum.denominator < compnum.numerator + compnum.whole * compnum.denominator;
	}
	bool operator<(const fraction& compnum) const {
		if (!this->isPos && compnum.isPos) {
			return true;
		}
		if (this->isPos && !compnum.isPos) {
			return false;
		}
		return ((this->numerator + (this->denominator * this->whole)) * compnum.denominator
				< (compnum.numerator + (compnum.denominator * compnum.whole)) * this->denominator)
				^ (!this->isPos && !compnum.isPos);
	}

	bool operator<=(const long int& compnum) const {
		return !(*this > compnum);
	}
	friend bool operator<=(const long int integer, const fraction& compnum) {
		return !(integer > compnum);
	}
	bool operator<=(const unsigned int& compnum) const {
		return !(*this > compnum);
	}
	friend bool operator<=(const unsigned int integer, const fraction& compnum) {
		return !(integer > compnum);
	}
	bool operator<=(const fraction& compnum) const {
		return !(*this > compnum);
	}

	bool operator>(const long int& compnum) const {
		if (this->isPos && compnum < 0) {
			return true;
		}
		if (!this->isPos && compnum > 0) {
			return false;
		}
		return (this->numerator + this->whole * this->denominator > compnum * this->denominator)
				^ (!this->isPos && compnum < 0);
	}
	friend bool operator>(const long int integer, const fraction& compnum) {
		if (!compnum.isPos && integer > 0) {
			return true;
		}
		if (compnum.isPos && integer < 0) {
			return false;
		}
		return (integer * compnum.denominator > compnum.numerator + (compnum.whole * compnum.denominator))
				^ (!compnum.isPos && integer < 0);
	}
	bool operator>(const unsigned int& compnum) const {
		if (!this->isPos) {
			return false;
		}
		return this->numerator + this->whole * this->denominator < compnum * this->denominator;
	}
	friend bool operator>(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return true;
		}
		return integer * compnum.denominator > compnum.numerator + compnum.whole * compnum.denominator;
	}
	bool operator>(const fraction& compnum) const {
		if (this->isPos && !compnum.isPos) {
			return true;
		}
		if (!this->isPos && compnum.isPos) {
			return false;
		}
		return ((this->numerator + (this->denominator * this->whole)) * compnum.denominator
				> (compnum.numerator + (compnum.denominator * compnum.whole)) * this->denominator)
				^ (!this->isPos && !compnum.isPos);
	}

	bool operator>=(const long int& compnum) const {
		return !(*this < compnum);
	}
	friend bool operator>=(const long int integer, const fraction& compnum) {
		return !(integer < compnum);
	}
	bool operator>=(const unsigned int& compnum) const {
		return !(*this < compnum);
	}
	friend bool operator>=(const unsigned int integer, const fraction& compnum) {
		return !(integer < compnum);
	}
	bool operator>=(const fraction& compnum) const {
		return !(*this < compnum);
	}

	bool operator==(const long int& compnum) const {
		if (this->isPos != compnum > 0) {
			return false;
		}
		return this->numerator + this->whole * this->denominator == compnum * this->denominator;
	}
	friend bool operator==(const long int integer, const fraction& compnum) {
		if (compnum.isPos != integer > 0) {
			return false;
		}
		return compnum.numerator + compnum.whole * compnum.denominator == integer * compnum.denominator;
	}
	bool operator==(const unsigned int& compnum) const {
		if (!this->isPos) {
			return false;
		}
		return this->numerator + this->whole * this->denominator == compnum * this->denominator;
	}
	friend bool operator==(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return false;
		}
		return compnum.numerator + compnum.whole * compnum.denominator == integer * compnum.denominator;
	}
	bool operator==(const fraction& compnum) const {
		if (this->isPos != compnum.isPos) {
			return false;
		}
		return (this->numerator + (this->denominator * this->whole)) * compnum.denominator
			== (compnum.numerator + (compnum.denominator * compnum.whole)) * this->denominator;
	}

	bool operator!=(const long int& compnum) const {
		return !(*this == compnum);
	}
	friend bool operator!=(const long int integer, const fraction& compnum) {
		return !(integer == compnum);
	}
	bool operator!=(const unsigned int& compnum) const {
		return !(*this == compnum);
	}
	friend bool operator!=(const unsigned int integer, const fraction& compnum) {
		return !(integer == compnum);
	}
	bool operator!=(const fraction& compnum) const {
		return !(*this == compnum);
	}

	explicit operator long int() const {
		return this->floored();
	}
	explicit operator unsigned int() const {
		return this->floored();
	}
	explicit operator bool() const {
		return this->numerator != 0 || this->whole != 0;
	}

	friend void LCD(fraction * f1, fraction * f2) {
		if (f1->denominator == f2->denominator) {
			return;
		}

		f1->reduce();
		f2->reduce();
		unsigned int LCD = f1->denominator * f2->denominator;
		if (f1->denominator % f2->denominator == 0) {
			LCD = f1->denominator;
		}
		else if (f2->denominator % f1->denominator == 0) {
			LCD = f2->denominator;
		}
		else {
			for (int i = 1; i <= f2->denominator; i++) {
				if ((f1->denominator * i) % f2->denominator == 0 || f2->denominator % (f1->denominator * i) == 0) {
					LCD = f1->denominator * i;
					break;
				}
			}
		}

		f1->numerator *= (LCD / f1->denominator);
		f2->numerator *= (LCD / f2->denominator);

		f1->denominator = LCD;
		f2->denominator = LCD;
	}

	friend std::istream& operator>>(std::istream& in, fraction& fract);
};

inline std::istream& operator>>(std::istream& in, fraction& fract) {
	// intended functionality:
	//		# &/% will read # into whole, & into numerator, % into denominator
	//		# will read # into whole
	//		&/% will read & into numerator, % into denominator
	return in;
}
inline std::ostream& operator<<(std::ostream& out, const fraction& fract) {
	return out << fract.toString();
}

#endif //FRACTIONS_FRACTION_H