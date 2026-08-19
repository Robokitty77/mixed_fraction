
#ifndef FRACTIONS_FRACTION_H
#define FRACTIONS_FRACTION_H


#include <string>
#include <stdexcept>

class fraction {
private:
	unsigned int numer, denom, who;
	bool isPos;
public:
	explicit fraction() : numer(0), denom(1), who(0), isPos(true) {};
	fraction(const long int num, const long int denom, const long int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}

		this->isPos = !(wh < 0 || (num < 0 ^ denom < 0));
		this->numer = abs(num);
		this->denom = abs(denom);
		this->who = abs(wh);
	}
	fraction(const int num, const int denom, const int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}

		this->isPos = !(wh < 0 || (num < 0 ^ denom < 0));
		this->numer = abs(num);
		this->denom = abs(denom);
		this->who = abs(wh);
	}
	fraction(const unsigned int num, const unsigned int denom, const unsigned int wh = 0) {
		if (denom == 0) {
			throw std::invalid_argument(std::to_string(num) + " / " + std::to_string(denom) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		this->isPos = true;
		this->numer = num;
		this->denom = denom;
		this->who = wh;
	}
	explicit fraction(const long int wh) {
		this->who = abs(wh);
		this->numer = 0;
		this->denom = 1;
		this->isPos = wh >= 0;
	}
	explicit fraction(const int wh) {
		this->who = abs(wh);
		this->numer = 0;
		this->denom = 1;
		this->isPos = wh >= 0;
	}
	explicit fraction(const unsigned int wh) {
		this->who = wh;
		this->numer = 0;
		this->denom = 1;
		this->isPos = true;
	}
	fraction(const fraction &other) {
		this->numer = other.numer;
		this->denom = other.denom;
		this->who = other.who;
		this->isPos = other.isPos;
	}

	~fraction() = default;

	[[nodiscard]] std::string toString() const {
		if (this->numer == 0) {
			return (this->isPos? "" : "-") +
				std::to_string(this->who);
		}
		if (this->who == 0) {
			return (this->isPos? "" : "-") +
				std::to_string(this->numer) + "/" +
				std::to_string(this->denom);
		}
		return (this->isPos? "" : "-") +
			std::to_string(this->who) + " " +
			std::to_string(this->numer) + "/" +
			std::to_string(this->denom);
	}

	void setWhole(long int wh) {
		this->who = wh;
		this->isPos = wh >= 0;
	}
	void setWhole(unsigned int wh) {
		this->who = wh;
	}
	void setNumerator(long int num) {
		this->numer = num;
		this->isPos = num >= 0;
	}
	void setNumerator(unsigned int num) {
		this->numer = num;
	}
	void setDenominator(long int denominator) {
		if (denominator == 0) {
			throw std::invalid_argument(std::to_string(this->numer) + " / " + std::to_string(denominator) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		this->denom = denominator;
		this->isPos = denominator >= 0;
	}
	void setDenominator(unsigned int denominator) {
		if (denominator == 0) {
			throw std::invalid_argument(std::to_string(this->numer) + " / " + std::to_string(denominator) +
				" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		this->denom = denominator;
	}

	bool balanceDenominatorAs(long int balancenum) {
		if (balancenum == 0) {
			throw std::invalid_argument(std::to_string(this->numer) + " / " + std::to_string(balancenum) +
	" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		if (this->denom == balancenum) {
			return true;
		}
		this->isPos = balancenum > 0;
		balancenum = abs(balancenum);
		if (this->numer == 0) {
			this->denom = balancenum;
			return true;
		}
		if (balancenum % this->denom == 0) {
			this->numer *= balancenum / this->denom;
			this->denom = balancenum;
			return true;
		}
		if (this->denom % balancenum == 0 && this->numer % (this->denom / balancenum) == 0) {
			this->numer /= this->denom / balancenum;
			this->denom = balancenum;
			return true;
		}
		fraction bsearch = *this;
		bsearch.denom = balancenum;
		fraction lesserfrac = *this;
		lesserfrac.denom = balancenum;
		fraction greaterfrac = *this;
		greaterfrac.denom = balancenum;

		unsigned int upper, lower;
		if (this->denom > balancenum) {
			upper = this->numer;
			lower = this->numer /
			((this->denom > balancenum?
				this->denom / balancenum :
				balancenum / this->denom)
			+ 1);
		}
		else {
			lower = this->numer;
			upper = this->numer *
			((this->denom > balancenum?
				this->denom / balancenum :
				balancenum / this->denom)
			+ 1);
		}

		do {
			lesserfrac.numer = bsearch.numer - 1;
			greaterfrac.numer = bsearch.numer + 1;
			if ((lesserfrac - *this).asPositive() > (bsearch - *this).asPositive()
				&& (greaterfrac - *this).asPositive() > (bsearch - *this).asPositive()) {
					break;
			}
			if ((lesserfrac - *this).asPositive() < (greaterfrac - *this).asPositive()) {
				upper = bsearch.numer;
				bsearch = (bsearch.numer + lower) / 2;
			}
			else {
				lower = bsearch.numer;
				bsearch = (bsearch.numer + upper) / 2;
			}
		} while (upper > lower);
		this->numer = bsearch.numer;
		return false;
	}
	bool balanceDenominatorAs(unsigned int balancenum) {
		if (balancenum == 0) {
			throw std::invalid_argument(std::to_string(this->numer) + " / " + std::to_string(balancenum) +
	" is not a valid fraction- \nDenominator value may not be zero\n");
		}
		if (this->denom == balancenum) {
			return true;
		}
		if (this->numer == 0) {
			this->denom = balancenum;
			return true;
		}
		if (balancenum % this->denom == 0) {
			this->numer *= balancenum / this->denom;
			this->denom = balancenum;
			return true;
		}
		if (this->denom % balancenum == 0 && this->numer % (this->denom / balancenum) == 0) {
			this->numer /= this->denom / balancenum;
			this->denom = balancenum;
			return true;
		}
		fraction bsearch = *this;
		bsearch.denom = balancenum;
		fraction lesserfrac = *this;
		lesserfrac.denom = balancenum;
		fraction greaterfrac = *this;
		greaterfrac.denom = balancenum;

		unsigned int upper, lower;
		if (this->denom > balancenum) {
			upper = balancenum;
			lower = this->numer /
			((this->denom > balancenum?
				this->denom / balancenum :
				balancenum / this->denom)
			+ 1);
		}
		else {
			lower = balancenum;
			upper = this->numer *
			((this->denom > balancenum?
				this->denom / balancenum :
				balancenum / this->denom)
			+ 1);
		}

		do {
			lesserfrac.numer = bsearch.numer - 1;
			greaterfrac.numer = bsearch.numer + 1;
			if ((lesserfrac - *this).asPositive() > (bsearch - *this).asPositive()
				&& (greaterfrac - *this).asPositive() > (bsearch - *this).asPositive()) {
					break;
			}
			if ((lesserfrac - *this).asPositive() < (greaterfrac - *this).asPositive()) {
				upper = bsearch.numer;
				bsearch = (bsearch.numer + lower) / 2;
			}
			else {
				lower = bsearch.numer;
				bsearch = (bsearch.numer + upper) / 2;
			}
		} while (upper > lower);
		this->numer = bsearch.numer;
		return false;
	}
	bool balanceNumeratorAs(long int balancenum) {
		if (this->numer == balancenum) {
			return true;
		}
		if ((balancenum <= (this->who * this->denom) + this->numer)
			&& this->isPos == balancenum > 0) {
			if (this->numer % this->denom == balancenum % this->denom) {
				if (balancenum > this->numer) {
					this->who -= (balancenum - this->numer) / this->denom;
				}
				else {
					this->who += (this->numer - balancenum) / this->denom;
				}
				this->numer = balancenum;
				return true;
			}
			if (balancenum > this->numer) {
				this->who -= (balancenum - this->numer) / this->denom + 1;
			}
			else {
				this->who += (this->numer - balancenum) / this->denom;
			}
			return false;
		}
		this->isPos = balancenum > 0;
		this->numer = abs(balancenum);
		this->who = 0;
		return false;
	}
	bool balanceNumeratorAs(unsigned int balancenum) {
		if (this->numer == balancenum) {
			return true;
		}
		if (balancenum <= (this->who * this->denom) + this->numer) {
			if (this->numer % this->denom == balancenum % this->denom) {
				if (balancenum > this->numer) {
					this->who -= (balancenum - this->numer) / this->denom;
				}
				else {
					this->who += (this->numer - balancenum) / this->denom;
				}
				this->numer = balancenum;
				return true;
			}
			if (balancenum > this->numer) {
				this->who -= (balancenum - this->numer) / this->denom + 1;
			}
			else {
				this->who += (this->numer - balancenum) / this->denom;
			}
			return false;
	}
		this->numer = balancenum;
		this->who = 0;
		return false;
	}
	bool balanceWholeAs(long int balancenum) {
		if (this->who == balancenum) {
			return true;
		}
		if ((this->denom * abs(balancenum) <= (this->who * this->denom) + this->numer)
			&& (this->isPos == balancenum > 0)) {
			if (this->who < balancenum) {
				this->numer -= (balancenum - this->who) * this->denom;
			}
			else {
				this->numer += (this->who - balancenum) * this->denom;
			}
			this->who = abs(balancenum);
			return true;
			}
		this->isPos = balancenum > 0;
		this->who = abs(balancenum);
		this->numer = 0;
		return false;
	}
	bool balanceWholeAs(unsigned int balancenum) {
		if (this->who == balancenum) {
			return true;
		}
		if (this->denom * balancenum <= (this->who * this->denom) + this->numer) {
			if (this->who < balancenum) {
				this->numer -= (balancenum - this->who) * this->denom;
			}
			else {
				this->numer += (this->who - balancenum) * this->denom;
			}
			this->who = balancenum;
			return true;
		}
		this->who = balancenum;
		this->numer = 0;
		return false;
	}

	[[nodiscard]] long int denominator() const {
		if (this->isPos) {
			return (long)this->denom;
		}
		return (long)this->denom * -1;
	}
	[[nodiscard]] long int numerator() const {
		if (this->isPos) {
			return (long)this->numer;
		}
		return (long)this->numer * -1;
	}
	[[nodiscard]] long int whole() const {
		if (this->isPos) {
			return (long)this->who;
		}
		return (long)this->who * -1;
	}
	[[nodiscard]] long int properNumerator() const {
		if (this->isPos) {
			return (long)(this->numer % this->denom);
		}
		return (long)(this->numer % this->denom) * -1;
	}
	[[nodiscard]] long int improperNumerator() const {
		if (this->isPos) {
			return (long)(this->numer) + (long)(this->who * this->denom);
		}
		return (long)(this->numer) + (long)(this->who * this->denom) * -1;
	}

	[[nodiscard]] long int floored() const {
		return (long)(this->who) + (long)(this->numer / this->denom);
	}
	[[nodiscard]] long int rounded() const {
		return ((this->numer % this->denom) * 2 >= this->denom)? this->ceilinged() : this->floored();
	}
	[[nodiscard]] long int ceilinged() const {
		return this->floored() + (((this->numer % this->denom) == 0)? 0: 1);
	}

	void floor() {
		this->numer -= (this->numer % this->denom);
	}
	void round() {
		if (this->numer % this->denom == 0) {
			return;
		}

		if ((this->numer % this->denom) * 2 >= this->denom) {
			this->numer += this->denom;
		}

		this->numer -= (this->numer % this->denom);
	}
	void ceiling() {
		if (this->numer % this->denom == 0) {
			return;
		}
		this->numer -= (this->numer % this->denom);
		this->numer += this->denom;
	}

	[[nodiscard]] bool isPositive() const {
		return this->isPos;
	}
	[[nodiscard]] bool isNegative() const {
		return !this->isPos;
	}
	[[nodiscard]] bool isReduced() const {
		if (this->numer == 0 || this->numer == 1 || this->denom == 1) {
			return true;
		}
		unsigned int upperbound = this->numer < this->denom? this->numer : this->denom;
		upperbound /= (upperbound % 2 == 0? 2 : 3);

		for (unsigned int i = 2; i <= upperbound; i++) {
			if (this->numer % i == 0 && this->denom % i == 0) {
				return false;
			}
		}
		return true;
	}
	[[nodiscard]] bool isProper() const {
		return this->numer < this->denom;
	}
	[[nodiscard]] bool isImproper() const {
		return this->numer > this->denom;
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
		if (this->numer == 0 || this->numer == 1 || this->denom == 1) {
			return;
		}
		if (this->numer % this->denom == 0) {
			this->numer /= this->denom;
			this->denom = 1;
			return;
		}
		if (this->denom % this->numer == 0) {
			this->denom /= this->numer;
			this->numer = 1;
			return;
		}
		unsigned int i = this->numer < this->denom? this->numer : this->denom;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2 ; i--) {
			if (this->numer % i == 0 && this->denom % i == 0) {
				this->numer /= i;
				this->denom /= i;
				return;
			}
		}
	}
	void proper() {
		this->who += this->numer / this->denom;
		this->numer %= this->denom;
	}
	void improper() {
		this->numer += this->denom * this->who;
		this->who = 0;
	}
	void invert() {
		unsigned long long int swapper = this->denom * this->who;
		swapper += this->numer;
		this->who = this->denom / swapper;
		this->numer = this->denom % swapper;
		this->denom = swapper;
	}

	fraction& operator=(const int& copynum) {
		this->numer = 0;
		this->who = abs(copynum);
		this->isPos = copynum >= 0;
		return *this;
	}
	fraction& operator=(const unsigned int& copynum) {
		this->numer = 0;
		this->who = copynum;
		this->isPos = true;
		return *this;
	}
	fraction& operator=(const fraction& copynum) {
		this->numer = copynum.numer;
		this->denom = copynum.denom;
		this->who = copynum.who;
		this->isPos = copynum.isPos;
		return *this;
	}

	fraction operator++() {
		if (this->isPos) {
			if (this->who != 0) {
				this->who++;
			}
			else {
				this->numer += this->denom;
			}
		}
		else {
			if (this->who == 0 && this->numer < this->denom) {
				this->numer = this->denom - this->numer;
				this->isPos = true;
			}
			else if (this->numer < this->denom) {
				this->who--;
			}
			else {
				this->numer -= this->denom;
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
			if (this->who != 0) {
				this->who++;
			}
			else {
				this->numer += this->denom;
			}
		}
		else {
			if (this->who == 0 && this->numer < this->denom) {
				this->numer = this->denom - this->numer;
				this->isPos = false;
			}
			else if (this->numer < this->denom) {
				this->who--;
			}
			else {
				this->numer -= this->denom;
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
			if (this->who == 0) {
				this->numer += (addnum * this->denom);
				return * this;
			}
			this->who += addnum;
			return * this;
		}

		if (this->who == 0) {
			if (addnum * this->denom < this->numer) {
				this->numer -= (addnum * this->denom);
				return * this;
			}
			this->isPos = true;
			this->numer = (addnum * this->denom) - this->numer;
			return * this;
		}

		if (this->who >= addnum) {
			this->who -= addnum;
			this->isPos = this->who == 0;
			return * this;
		}

		if (this->numer >= addnum * this->denom) {
			this->numer -= (addnum * this->denom);
			return * this;
		}

		long int copynum = addnum;
		copynum -= (long)this->who;
		this->who = 0;

		return *this += copynum;
	}
	friend long int operator+=(long int integer, const fraction& addnum) {
		return integer + addnum.floored();
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
			if (this->who == 0) {
				this->numer += (addnum * this->denom);
				return * this;
			}
			this->who += addnum;
			return * this;
		}

		if (this->who == 0) {
			if (addnum * this->denom < this->numer) {
				this->numer -= (addnum * this->denom);
				return * this;
			}
			this->isPos = true;
			this->numer = (addnum * this->denom) - this->numer;
			return * this;
		}

		if (this->who >= addnum) {
			this->who -= addnum;
			this->isPos = this->who == 0;
			return * this;
		}

		if (this->numer >= addnum * this->denom) {
			this->numer -= (addnum * this->denom);
			return * this;
		}

		unsigned int copynum = addnum;
		copynum -= this->who;
		this->who = 0;

		return * this += copynum;
	}
	friend unsigned int operator+=(unsigned int integer, const fraction& addnum) {
		return integer + addnum.floored();
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
			this->who += fractioncopy.who;
			this->numer += fractioncopy.numer;
			return * this;
		}

		// the approach for adding a positive number to a negative number
		// changes based on a sign change is necessary or not
		// if the two are equivalent, the net value will just be 0
		if (*this == fractioncopy) {
			this->who = 0;
			this->numer = 0;
			this->isPos = true;
			return * this;
		}
		// if this is smaller than the number being added to it, the sign bool will need to flip
		// and the magnitude of the fraction afterwards will be fractioncopy - *this
		if (*this < fractioncopy) {
			this->isPos = true;
			if (this->who < fractioncopy.who) {
				fractioncopy.who -= this->who;
				this->who = 0;
				if (this->numer < fractioncopy.who * fractioncopy.denom) {
					this->who = fractioncopy.who + (fractioncopy.numer / fractioncopy.denom);
					this->numer = (fractioncopy.numer % fractioncopy.denom) - this->numer;
					return * this;
				}
				this->numer -= fractioncopy.who * fractioncopy.denom;
				this->numer = (fractioncopy.numer % fractioncopy.denom) - this->numer;
				this->who = fractioncopy.numer / fractioncopy.denom;
				return * this;
			}

			this->who -= fractioncopy.who;
			// fractioncopy's value has to have started as being higher than *this'
			// arriving here specifically means that its numerator is larger than *this'
			fractioncopy.numer -= this->who * this->denom;
			this->who = 0;
			this->numer = fractioncopy.numer - this->numer;
			return * this;
		}

		// if *this is larger than the number being added to it, the sign bool will not flip
		// and the magnitude of the fraction afterwards will be *this - fractioncopy
		if (this->who < fractioncopy.who) {
			fractioncopy.who -= this->who;
			this->who = 0;
			this->numer -= fractioncopy.who * fractioncopy.denom;
			this->numer -= fractioncopy.numer;
			return * this;
		}
		this->who -= fractioncopy.who;
		if (this->numer < fractioncopy.numer) {
			this->who -= fractioncopy.numer / fractioncopy.denom;
			fractioncopy.numer %= fractioncopy.denom;
		}
		this->numer -= fractioncopy.numer;
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
			if (this->who == 0) {
				this->numer += (subnum * this->denom);
				return * this;
			}
			this->who += subnum;
			return * this;
		}

		if (this->who == 0) {
			if (subnum * this->denom < this->numer) {
				this->numer -= (subnum * this->denom);
				return * this;
			}
			this->isPos = false;
			this->numer = (subnum * this->denom) - this->numer;
			return * this;
		}

		if (this->who >= subnum) {
			this->who -= subnum;
			return * this;
		}

		if (this->numer >= subnum * this->denom) {
			this->numer -= (subnum * this->denom);
			return * this;
		}

		long int copynum = subnum;
		copynum -= (long)this->who;
		this->who = 0;

		return * this -= copynum;
	}
	friend long int operator-=(long int integer, const fraction& subnum) {
		if (!subnum.isPos) {
			return integer += subnum.asPositive();
		}
		if (integer >=0 && integer < subnum) {
			integer -= subnum.floored();
			return integer;
		}
		integer -= subnum.ceilinged();
		return integer;
	}
	fraction operator-(const long int& subnum) const {
		fraction result(*this);
		result -= subnum;
		return result;
	}
	friend fraction operator-(const long int integer, const fraction& subnum) {
		if (!subnum.isPos) {
			return integer + subnum.asPositive();
		}
		fraction result(integer);
		result -= subnum;
		return result;
	}
	fraction operator-=(const unsigned int& subnum) {
		if (!this->isPos) {
			if (this->who == 0) {
				this->numer += (subnum * this->denom);
				return * this;
			}
			this->who += subnum;
			return * this;
		}

		if (this->who == 0) {
			if (subnum * this->denom < this->numer) {
				this->numer -= (subnum * this->denom);
				return * this;
			}
			this->isPos = false;
			this->numer = (subnum * this->denom) - this->numer;
			return * this;
		}

		if (this->who >= subnum) {
			this->who -= subnum;
			return * this;
		}

		if (this->numer >= subnum * this->denom) {
			this->numer -= (subnum * this->denom);
			return * this;
		}

		unsigned int copynum = subnum;
		copynum -= this->who;
		this->who = 0;

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
			this->who += fractioncopy.who;
			this->numer += fractioncopy.numer;
			return * this;
		}

		// the approach for subtracting a positive number from another positive number
		// changes based on a sign change is necessary or not
		// if the two are equivalent, the net value will just be 0
		if (*this == fractioncopy) {
			this->who = 0;
			this->numer = 0;
			this->isPos = true;
			return * this;
		}
		// if *this is smaller than the number being subtracted from it, the sign bool will need to flip
		// and the magnitude of the fraction afterwards will be fractioncopy - *this
		if (*this < fractioncopy) {
			this->isPos = false;
			if (this->who < fractioncopy.who) {
				fractioncopy.who -= this->who;
				this->who = 0;
				if (this->numer < fractioncopy.who * fractioncopy.denom) {
					this->who = fractioncopy.who + (fractioncopy.numer / fractioncopy.denom);
					this->numer = (fractioncopy.numer % fractioncopy.denom) - this->numer;
					return * this;
				}
				this->numer -= fractioncopy.who * fractioncopy.denom;
				this->numer = (fractioncopy.numer % fractioncopy.denom) - this->numer;
				this->who = fractioncopy.numer / fractioncopy.denom;
				return * this;
			}

			this->who -= fractioncopy.who;
			// fractioncopy's value has to have started as being higher than *this'
			// arriving here specifically means that its numerator is larger than *this'
			fractioncopy.numer -= this->who * this->denom;
			this->who = 0;
			this->numer = fractioncopy.numer - this->numer;
			return * this;
		}

		// if *this is larger than the number being subtracted from it, the sign bool will not flip
		// and the magnitude of the fraction afterwards will be *this - fractioncopy
		if (this->who < fractioncopy.who) {
			fractioncopy.who -= this->who;
			this->who = 0;
			this->numer -= fractioncopy.who * fractioncopy.denom;
			this->numer -= fractioncopy.numer;
			return * this;
		}
		this->who -= fractioncopy.who;
		if (this->numer < fractioncopy.numer) {
			this->who -= fractioncopy.numer / fractioncopy.denom;
			fractioncopy.numer %= fractioncopy.denom;
		}
		this->numer -= fractioncopy.numer;
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
		unsigned int copynum = abs(multnum);
		this->who *= copynum;

		if (this->denom % copynum == 0) {
			this->denom /= copynum;
			return * this;
		}
		unsigned int i = copynum;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (copynum % i == 0) {
				if (this->denom % (copynum / i) == 0) {
					copynum /= i;
					this->denom /= copynum;
					break;
				}
			}
		}
		this->numer *= copynum;
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
		this->who *= copynum;
		if (this->denom % copynum == 0) {
			this->denom /= copynum;
			return * this;
		}
		unsigned int i = copynum;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (copynum % i == 0) {
				if (this->denom % (copynum / i) == 0) {
					copynum /= i;
					this->denom /= copynum;
					break;
				}
			}
		}
		this->numer *= copynum;
		return * this;
	}
	friend unsigned int operator*=(unsigned int integer, const fraction& multnum) {
		fraction fractioncopy(multnum);
		fractioncopy *= integer;
		return fractioncopy.floored();
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
		if (this->who != 0) {
			unsigned int wholestorage = this->who;
			this->who = 0;
			return (wholestorage * copynum) + (*this * copynum);
		}
		if (copynum.who != 0) {
			unsigned int wholestorage = copynum.who;
			copynum.who = 0;
			return (*this * wholestorage) + (*this * copynum);
		}

		if (this->numer % copynum.denom == 0) {
			this->numer /= copynum.denom;
			copynum.denom = 1;
		}
		else if (copynum.denom % this->numer == 0) {
			copynum.denom /= this->numer;
			this->numer = 1;
		}
		else {
			unsigned int i1 = (this->numer < copynum.denom? this->numer : copynum.denom);
			i1 /= (i1 % 2 == 0? 2 : 3);
			for (; i1 >= 2; i1--) {
				if (this->numer % i1 == 0 && copynum.denom % i1 == 0) {
					this->numer /= i1;
					copynum.denom /= i1;
				}
			}
		}

		if (copynum.numer % this->denom == 0) {
			copynum.numer /= this->denom;
			this->denom = 1;
		}
		else if (this->denom % copynum.numer == 0) {
			this->denom /= copynum.numer;
			copynum.numer = 1;
		}
		else {
			unsigned int i2 = (copynum.numer < this->denom? copynum.numer : this->denom);
			i2 /= (i2 % 2 == 0? 2 : 3);
			for (; i2 >= 2; i2--) {
				if (copynum.numer % i2 == 0 && this->denom % i2 == 0) {
					copynum.numer /= i2;
					this->denom /= i2;
				}
			}
		}

		this->reduce();
		copynum.reduce();

		this->numer *= copynum.numer;
		this->denom *= copynum.denom;

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
		unsigned long long int impnum = this->denom * this->who;
		impnum += this->numer;
		this->who = 0;
		if (divnum < 0) {
			this->isPos = !this->isPos;
		}
		int copynum = divnum;
		if (impnum % copynum == 0) {
			this->numer = impnum / copynum;
			return * this;
		}

		long int i = copynum;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (copynum % i == 0) {
				if (this->numer % (copynum / i) == 0) {
					copynum /= i;
					this->numer /= copynum;
					break;
				}
			}
		}
		this->denom *= copynum;
		return * this;
	}
	friend long int operator/=(long int integer, const fraction& divnum) {
		bool mismatch = integer > 0 != divnum.isPos;
		integer = abs(integer);
		fraction fractioncopy(divnum);
		unsigned long long int impnum = fractioncopy.denom * fractioncopy.who;
		impnum += fractioncopy.numer;
		fractioncopy.who = 0;

		if (impnum % integer == 0) {
			fractioncopy.numer /= integer;
			integer = fractioncopy.floored();
			if (mismatch) {
				integer *= -1;
			}
			return integer;
		}

		long int i = integer;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (integer % i == 0) {
				if (impnum % (integer / i) == 0) {
					integer /= i;
					fractioncopy.numer /= integer;
					break;
				}
			}
		}
		fractioncopy.denom *= integer;
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
		unsigned long long int impnum = this->denom * this->who;
		impnum += this->numer;
		this->who = 0;

		unsigned int copynum = divnum;
		if (impnum % copynum == 0) {
			this->numer = impnum / copynum;
			return * this;
		}

		unsigned int i = copynum;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (copynum % i == 0) {
				if (impnum % (copynum / i) == 0) {
					copynum /= i;
					this->numer = impnum / copynum;
					break;
				}
			}
		}
		this->denom *= copynum;
		return * this;
	}
	friend unsigned int operator/=(unsigned int integer, const fraction& divnum) {
		fraction fractioncopy(divnum);
		unsigned long long int impnum = fractioncopy.denom * fractioncopy.who;
		impnum += fractioncopy.numer;
		fractioncopy.who = 0;

		if (impnum % integer == 0) {
			fractioncopy.numer /= integer;
			return fractioncopy.floored();
		}

		unsigned int i = integer;
		i /= (i % 2 == 0? 2 : 3);
		for (; i >= 2; i--) {
			if (integer % i == 0) {
				if (fractioncopy.numer % (integer / i) == 0) {
					integer /= i;
					fractioncopy.numer /= integer;
					break;
				}
			}
		}
		fractioncopy.denom *= integer;
		return fractioncopy.floored();
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
		unsigned long long int impnum = this->denom * this->who;
		// it is still possible for this addition to overflow, though
		impnum += this->numer;
		// impdenom, or improper denominator, follows the same logic but for divnum
		// it's the "denominator" even though it uses the same formula
		// to model fraction division being an inversion + multiplication
		unsigned long long int impdenom = divnum.denom * divnum.who;
		impdenom += divnum.numer;
		// divnum's denominator needs to be editable, it is the numerator of the inverted fraction
		unsigned int numeratorcopy = divnum.denom;
		// impnum has already taken into account the value of this' whole portion
		this->who = 0;

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
					// mathamatically, if both a and b divide them evenly,
					// i1 must have equaled a*b or higher at the start
					// ergo, once a loop that can divide is executed, the others are functionally insignificant
					if (impnum % i1 == 0 && impdenom % i1 == 0) {
						impnum /= i1;
						impdenom /= i1;
						break;
					}
				}
			}
		}

		// this is a repeat of the above logic but with the other cross pairing of numerator and denominator
		if (numeratorcopy != 0 && numeratorcopy != 1) {
			if (numeratorcopy % this->denom == 0) {
				numeratorcopy /= this->denom;
				this->denom = 1;
			}
			else if (this->denom % numeratorcopy == 0) {
				this->denom /= numeratorcopy;
				numeratorcopy = 1;
			}
			else {
				unsigned int i2 = (numeratorcopy < this->denom? numeratorcopy : this->denom);
				i2 /= (i2 % 2 == 0? 2 : 3);
				for (; i2 >= 2; i2--) {
					if (numeratorcopy % i2 == 0 && this->denom % i2 == 0) {
						numeratorcopy /= i2;
						this->denom /= i2;
						break;
					}
				}
			}
		}
		// end repeat of logic

		// below is essentially the .reduce() method twice, but with slightly different logic
		// to work on a discrete pair of variables and not an object
		if (impnum != 0 && impnum != 1) {
			if (impnum % this->denom == 0) {
				impnum /= this->denom;
				this->denom = 1;
			}
			else if (this->denom % impnum == 0) {
				this->denom /= impnum;
				impnum = 1;
			}
			else {
				unsigned int i3 = (impnum < this->denom? impnum : this->denom);
				i3 /= (i3 % 2 == 0? 2 : 3);
				for (; i3 >= 2 ; i3--) {
					if (impnum % i3 == 0 && this->denom % i3 == 0) {
						impnum /= i3;
						this->denom /= i3;
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
						break;
					}
				}
			}
		}

		// after the above, the numbers are as low as conceivably possible
		// in the future, this is where a check for overflow will go and an error possibly thrown
		this->numer = impnum * numeratorcopy;
		this->denom *= impdenom;
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
		this->isPos = true;
		unsigned long long int impnum = this->denom * this->who;
		impnum += this->numer;
		impnum %= (modnum * this->denom);

		this->who = impnum / this->denom;
		this->numer = impnum % this->denom;
		return * this;
	}
	friend long int operator%=(long int integer, const fraction& modnum) {
		integer = abs(integer);
		integer *= (long)modnum.denom;
		integer %= (long)(modnum.numer + (modnum.denom * modnum.who));
		integer /= (long)modnum.denom;
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
		this->isPos = true;
		unsigned long long int impnum = this->denom * this->who;
		impnum += this->numer;
		impnum %= (modnum * this->denom);

		this->who = impnum / this->denom;
		this->numer = impnum % this->denom;
		return * this;
	}
	friend unsigned int operator%=(unsigned int integer, const fraction& modnum) {
		integer *= (long)modnum.denom;
		integer %= (long)(modnum.numer + (modnum.denom * modnum.who));
		integer /= (long)modnum.denom;
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
		return (this->numer + this->who * this->denom < compnum * this->denom)
				^ (!this->isPos && compnum < 0);
	}
	friend bool operator<(const long int integer, const fraction& compnum) {
		if (compnum.isPos && integer < 0) {
			return true;
		}
		if (!compnum.isPos && integer > 0) {
			return false;
		}
		return (integer * compnum.denom < compnum.numer + (compnum.who * compnum.denom))
				^ (!compnum.isPos && integer < 0);
	}
	bool operator<(const unsigned int& compnum) const {
		if (!this->isPos) {
			return true;
		}
		return this->numer + this->who * this->denom < compnum * this->denom;
	}
	friend bool operator<(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return false;
		}
		return integer * compnum.denom < compnum.numer + compnum.who * compnum.denom;
	}
	bool operator<(const fraction& compnum) const {
		if (!this->isPos && compnum.isPos) {
			return true;
		}
		if (this->isPos && !compnum.isPos) {
			return false;
		}
		return ((this->numer + (this->denom * this->who)) * compnum.denom
				< (compnum.numer + (compnum.denom * compnum.who)) * this->denom)
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
		return (this->numer + this->who * this->denom > compnum * this->denom)
				^ (!this->isPos && compnum < 0);
	}
	friend bool operator>(const long int integer, const fraction& compnum) {
		if (!compnum.isPos && integer > 0) {
			return true;
		}
		if (compnum.isPos && integer < 0) {
			return false;
		}
		return (integer * compnum.denom > compnum.numer + (compnum.who * compnum.denom))
				^ (!compnum.isPos && integer < 0);
	}
	bool operator>(const unsigned int& compnum) const {
		if (!this->isPos) {
			return false;
		}
		return this->numer + this->who * this->denom < compnum * this->denom;
	}
	friend bool operator>(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return true;
		}
		return integer * compnum.denom > compnum.numer + compnum.who * compnum.denom;
	}
	bool operator>(const fraction& compnum) const {
		if (this->isPos && !compnum.isPos) {
			return true;
		}
		if (!this->isPos && compnum.isPos) {
			return false;
		}
		return ((this->numer + (this->denom * this->who)) * compnum.denom
				> (compnum.numer + (compnum.denom * compnum.who)) * this->denom)
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
		return this->numer + this->who * this->denom == compnum * this->denom;
	}
	friend bool operator==(const long int integer, const fraction& compnum) {
		if (compnum.isPos != integer > 0) {
			return false;
		}
		return compnum.numer + compnum.who * compnum.denom == integer * compnum.denom;
	}
	bool operator==(const unsigned int& compnum) const {
		if (!this->isPos) {
			return false;
		}
		return this->numer + this->who * this->denom == compnum * this->denom;
	}
	friend bool operator==(const unsigned int integer, const fraction& compnum) {
		if (!compnum.isPos) {
			return false;
		}
		return compnum.numer + compnum.who * compnum.denom == integer * compnum.denom;
	}
	bool operator==(const fraction& compnum) const {
		if (this->isPos != compnum.isPos) {
			return false;
		}
		return (this->numer + (this->denom * this->who)) * compnum.denom
			== (compnum.numer + (compnum.denom * compnum.who)) * this->denom;
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
		return this->numer != 0 || this->who != 0;
	}

	friend void LCD(fraction * f1, fraction * f2) {
		if (f1->denom == f2->denom) {
			return;
		}

		f1->reduce();
		f2->reduce();
		unsigned int LCD = f1->denom * f2->denom;
		if (f1->denom % f2->denom == 0) {
			LCD = f1->denom;
		}
		else if (f2->denom % f1->denom == 0) {
			LCD = f2->denom;
		}
		else {
			for (int i = 1; i <= f2->denom; i++) {
				if ((f1->denom * i) % f2->denom == 0 || f2->denom % (f1->denom * i) == 0) {
					LCD = f1->denom * i;
					break;
				}
			}
		}

		f1->numer *= (LCD / f1->denom);
		f2->numer *= (LCD / f2->denom);

		f1->denom = LCD;
		f2->denom = LCD;
	}

	friend std::istream& operator>>(std::istream& in, fraction& fract);
};

inline std::istream& operator>>(std::istream& in, fraction& fract) {
	// intended functionality:
	// read in formats N/D or W N/D
	// fraction will be marked as negative if any number is preceded by a dash
	return in;
}
inline std::ostream& operator<<(std::ostream& out, const fraction& fract) {
	return out << fract.toString();
}


#endif //FRACTIONS_FRACTION_H