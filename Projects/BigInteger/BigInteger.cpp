#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class BigInt {
 public:
  BigInt();

  BigInt(int64_t n);

  BigInt(std::string str);

  BigInt(const BigInt& other);

  BigInt& operator=(const BigInt& other);

  void Check();

  void Clear();

  std::vector<uint64_t> Number();

  void ChangeNumber(std::vector<uint64_t> new_number);

  void ChangeSign(char new_sign);

  size_t Size() const;

  char Sign() const;

  uint64_t& operator[](size_t index);

  const uint64_t& operator[](size_t index) const;

  BigInt& operator+=(const BigInt& other);

  BigInt operator+(const BigInt& other) const;

  BigInt& operator-=(const BigInt& other);

  BigInt operator-(const BigInt& other) const;

  BigInt& operator*=(const BigInt& other);

  BigInt operator*(const BigInt& other) const;

  BigInt& operator/=(const BigInt& other);

  BigInt operator/(const BigInt& other) const;

  BigInt& operator%=(const BigInt& other);

  BigInt operator%(const BigInt& other) const;

  BigInt operator++();

  BigInt operator++(int);

  BigInt operator--();

  BigInt operator--(int);

  BigInt operator-() const;

  void Print() const;

 private:
  std::vector<uint64_t> number_;
  char sign_;
};

std::vector<uint64_t> Plus(std::vector<uint64_t> astr,
                           std::vector<uint64_t> bstr);

std::vector<uint64_t> Minus(std::vector<uint64_t> astr,
                            std::vector<uint64_t> bstr);

std::vector<uint64_t> Multiply(std::vector<uint64_t> astr,
                               std::vector<uint64_t> bstr);

BigInt Div2(BigInt xstr);

bool operator==(const BigInt& nstr, const BigInt& mstr);

bool operator!=(const BigInt& nstr, const BigInt& mstr);

bool Compare(const BigInt& nstr, const BigInt& mstr);

bool operator<(const BigInt& nstr, const BigInt& mstr);

bool operator<=(const BigInt& nstr, const BigInt& mstr);

bool operator>(const BigInt& nstr, const BigInt& mstr);

bool operator>=(const BigInt& nstr, const BigInt& mstr);

std::istream& operator>>(std::istream& input, BigInt& nstr);

std::ostream& operator<<(std::ostream& output, const BigInt& nstr);

const uint64_t kTen = 10;
const uint64_t kZero = 48;
const uint64_t kNine = 9;

BigInt::BigInt() {
  sign_ = '0';
  number_.push_back(0);
}

BigInt::BigInt(int64_t n) {
  if (n < 0) {
    sign_ = '-';
    n *= -1;
  } else if (n > 0) {
    sign_ = '+';
  } else {
    sign_ = '0';
  }
  if (n == 0) {
    number_.push_back(0);
  }
  while (n != 0) {
    number_.push_back(n % kTen);
    n /= kTen;
  }
  reverse(number_.begin(), number_.end());
}

BigInt::BigInt(std::string str) {
  int begin = 0;
  if (str[0] == '-') {
    sign_ = '-';
    begin = 1;
  } else if (str[0] == '0') {
    sign_ = '0';
  } else {
    sign_ = '+';
  }
  if (str[begin] == '0') {
    sign_ = '0';
    number_.push_back(0);
  } else {
    for (size_t i = begin; i < str.size(); i++) {
      number_.push_back(int(str[i]) - kZero);
    }
  }
}

BigInt::BigInt(const BigInt& other) { *this = other; }

BigInt& BigInt::operator=(const BigInt& other) {
  number_ = other.number_;
  sign_ = other.sign_;
  return *this;
}

void BigInt::Clear() {
  std::vector<uint64_t> clear;
  clear.push_back(0);
  number_ = clear;
  sign_ = '0';
}

void BigInt::Check() {
  if (number_.size() == 1 && number_[0] == 0) {
    return;
  }
  reverse(number_.begin(), number_.end());
  while (number_.back() == 0) {
    number_.erase(number_.end() - 1);
  }
  reverse(number_.begin(), number_.end());
}

std::vector<uint64_t> BigInt::Number() { return number_; }

void BigInt::ChangeNumber(std::vector<uint64_t> new_number) {
  number_ = new_number;
}

void BigInt::ChangeSign(char new_sign) { sign_ = new_sign; }

size_t BigInt::Size() const { return number_.size(); }

char BigInt::Sign() const { return sign_; }

uint64_t& BigInt::operator[](size_t index) { return number_[index]; }

const uint64_t& BigInt::operator[](size_t index) const {
  return number_[index];
}

std::vector<uint64_t> Plus(std::vector<uint64_t> astr,
                           std::vector<uint64_t> bstr) {
  reverse(astr.begin(), astr.end());
  reverse(bstr.begin(), bstr.end());
  std::vector<uint64_t> result;
  uint64_t reminder = 0;
  uint64_t minim = std::min(bstr.size(), astr.size());
  uint64_t maxim = std::max(bstr.size(), astr.size());
  for (size_t i = 0; i < minim; i++) {
    uint64_t curr = astr[i] + bstr[i] + reminder;
    result.push_back(curr % kTen);
    reminder = curr / kTen;
  }
  for (size_t i = minim; i < maxim; i++) {
    uint64_t curr = astr.size() > bstr.size() ? astr[i] : bstr[i];
    curr += reminder;
    result.push_back(curr % kTen);
    reminder = curr / kTen;
  }
  if (reminder > 0) {
    result.push_back(reminder);
  }
  reverse(result.begin(), result.end());
  return result;
}

std::vector<uint64_t> Minus(std::vector<uint64_t> astr,
                            std::vector<uint64_t> bstr) {
  reverse(astr.begin(), astr.end());
  reverse(bstr.begin(), bstr.end());
  std::vector<uint64_t> result;
  for (size_t i = 0; i < bstr.size(); i++) {
    if (astr[i] >= bstr[i]) {
      result.push_back(astr[i] - bstr[i]);
    } else {
      int ind = i + 1;
      while (i < astr.size() && astr[ind] == 0) {
        ind++;
      }
      astr[ind]--;
      for (size_t j = ind - 1; j > i; j--) {
        astr[j] = kNine;
      }
      astr[i] += kTen;
      result.push_back(astr[i] - bstr[i]);
    }
  }
  for (size_t i = bstr.size(); i < astr.size(); i++) {
    result.push_back(astr[i]);
  }
  while (result.back() == 0) {
    result.erase(result.end() - 1);
  }
  reverse(result.begin(), result.end());
  return result;
}

std::vector<uint64_t> Multiply(std::vector<uint64_t> astr,
                               std::vector<uint64_t> bstr) {
  reverse(astr.begin(), astr.end());
  reverse(bstr.begin(), bstr.end());
  std::vector<uint64_t> result(astr.size() + bstr.size());
  uint64_t reminder = 0;
  for (size_t j = 0; j < bstr.size(); j++) {
    for (size_t i = 0; i < astr.size(); i++) {
      uint64_t curr = astr[i] * bstr[j] + reminder;
      result[i + j] += curr % kTen;
      reminder = curr / kTen;
    }
    if (reminder > 0) {
      result[j + astr.size()] += reminder;
      reminder = 0;
    }
  }
  for (size_t i = 0; i < result.size() - 1; i++) {
    result[i + 1] += result[i] / kTen;
    result[i] %= kTen;
  }
  while (result.back() == 0) {
    result.erase(result.end() - 1);
  }
  reverse(result.begin(), result.end());
  return result;
}

std::vector<uint64_t> Div2(std::vector<uint64_t> xstr) {
  std::vector<uint64_t> result;
  uint64_t reminder = 0;
  size_t ind = 0;
  bool empty = true;
  while (ind < xstr.size()) {
    uint64_t curr = reminder * kTen + xstr[ind];
    while (curr < 2) {
      ind++;
      if (ind == xstr.size()) {
        break;
      }
      result.push_back(0);
      curr = curr * kTen + xstr[ind];
    }
    result.push_back(curr / 2);
    empty = false;
    reminder = curr % 2;
    ind++;
  }
  return result;
}

BigInt& BigInt::operator+=(const BigInt& other) {
  if (sign_ == '0') {
    *this = other;
  } else if (sign_ == other.sign_) {
    number_ = Plus(this->number_, other.number_);
  } else if (sign_ == '+' && other.sign_ == '-') {
    BigInt copy = other;
    copy.sign_ = '+';
    if (*this > copy) {
      number_ = Minus(this->number_, other.number_);
    } else if (*this < copy) {
      sign_ = '-';
      number_ = Minus(other.number_, this->number_);
    } else if (*this == copy) {
      this->Clear();
    }
  } else if (sign_ == '-' && other.sign_ == '+') {
    BigInt copy = *this;
    copy.sign_ = '+';
    if (copy > other) {
      number_ = Minus(this->number_, other.number_);
    } else if (copy < other) {
      sign_ = '+';
      number_ = Minus(other.number_, this->number_);
    } else {
      this->Clear();
    }
  }
  return *this;
}

BigInt BigInt::operator+(const BigInt& other) const {
  BigInt copy = *this;
  copy += other;
  return copy;
}

BigInt& BigInt::operator-=(const BigInt& other) {
  BigInt copy = other;
  if (copy.sign_ == '-') {
    copy.sign_ = '+';
  } else if (copy.sign_ == '+') {
    copy.sign_ = '-';
  }
  *this += copy;
  return *this;
}

BigInt BigInt::operator-(const BigInt& other) const {
  BigInt copy = *this;
  copy -= other;
  return copy;
}

BigInt& BigInt::operator*=(const BigInt& other) {
  if (sign_ == '0' || other.sign_ == '0') {
    this->Clear();
    return *this;
  }
  sign_ = sign_ == other.sign_ ? '+' : '-';
  number_ = Multiply(number_, other.number_);
  return *this;
}

BigInt BigInt::operator*(const BigInt& other) const {
  BigInt copy = *this;
  copy *= other;
  return copy;
}

BigInt& BigInt::operator/=(const BigInt& other) {
  if (other.sign_ == '0') {
    std::cout << "Error\n";
    exit(-1);
  } else if (sign_ == '0') {
    return *this;
  }
  BigInt copy1 = *this;
  BigInt copy2 = other;
  copy1.sign_ = copy2.sign_ = '+';
  if (copy2 > copy1) {
    this->Clear();
    return *this;
  }
  BigInt left(1);
  BigInt right = copy1;
  while (right - left > 1) {
    BigInt mid = left + right;
    mid.number_ = Div2(mid.number_);
    if (mid * copy2 > copy1) {
      right = mid;
    } else {
      left = mid;
    }
  }
  this->number_ = right * copy2 == copy1 ? right.number_ : left.number_;
  sign_ = sign_ == other.sign_ ? '+' : '-';
  this->Check();
  return *this;
}

BigInt BigInt::operator/(const BigInt& other) const {
  BigInt copy = *this;
  copy /= other;
  return copy;
}

BigInt& BigInt::operator%=(const BigInt& other) {
  *this = *this - (*this / other) * other;
  return *this;
}

BigInt BigInt::operator%(const BigInt& other) const {
  BigInt copy = *this;
  copy %= other;
  return copy;
}

BigInt BigInt::operator++() {
  *this += 1;
  return *this;
}

BigInt BigInt::operator++(int) {
  BigInt copy = *this;
  *this += 1;
  return copy;
}

BigInt BigInt::operator--() { return *this -= 1; }

BigInt BigInt::operator--(int) {
  BigInt copy = *this;
  *this -= 1;
  return copy;
}

BigInt BigInt::operator-() const {
  BigInt copy = *this;
  if (copy.sign_ == '-') {
    copy.sign_ = '+';
  } else if (copy.sign_ == '+') {
    copy.sign_ = '-';
  }
  return copy;
}

bool operator==(const BigInt& nstr, const BigInt& mstr) {
  if (nstr.Size() != mstr.Size() || nstr.Sign() != mstr.Sign()) {
    return false;
  }
  for (size_t i = 0; i < nstr.Size(); i++) {
    if (nstr[i] != mstr[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const BigInt& nstr, const BigInt& mstr) {
  return !(nstr == mstr);
}

bool Compare(const BigInt& nstr, const BigInt& mstr) {
  if (nstr.Size() < mstr.Size()) {
    return true;
  }
  if (nstr.Size() > mstr.Size()) {
    return false;
  }
  for (size_t i = 0; i < nstr.Size(); i++) {
    if (nstr[i] > mstr[i]) {
      return false;
    }
    if (nstr[i] < mstr[i]) {
      return true;
    }
  }
  return false;
}

bool operator<(const BigInt& nstr, const BigInt& mstr) {
  if ((nstr.Sign() == '-' && mstr.Sign() != '-') ||
      (nstr.Sign() == '0' && mstr.Sign() == '+')) {
    return true;
  }
  if ((nstr.Sign() == '+' && mstr.Sign() != '+') ||
      (nstr.Sign() == '0' && mstr.Sign() == '-')) {
    return false;
  }
  if (nstr.Sign() == '+' && mstr.Sign() == '+') {
    return Compare(nstr, mstr);
  }
  if (nstr.Sign() == '-' && mstr.Sign() == '-') {
    return !Compare(nstr, mstr);
  }
  return false;
}

bool operator<=(const BigInt& nstr, const BigInt& mstr) {
  return nstr == mstr ? true : nstr < mstr;
}

bool operator>(const BigInt& nstr, const BigInt& mstr) {
  return !(nstr <= mstr);
}

bool operator>=(const BigInt& nstr, const BigInt& mstr) {
  return nstr == mstr ? true : nstr > mstr;
}

std::istream& operator>>(std::istream& input, BigInt& nstr) {
  std::string str;
  input >> str;
  nstr = str;
  return input;
}

std::ostream& operator<<(std::ostream& output, const BigInt& nstr) {
  if (nstr.Sign() == '-') {
    output << '-';
  }
  for (size_t i = 0; i < nstr.Size(); i++) {
    output << nstr[i];
  }
  return output;
}

void BigInt::Print() const {
  if (sign_ == '-') {
    std::cout << sign_;
  }
  for (size_t i = 0; i < number_.size(); i++) {
    std::cout << number_[i];
  }
  std::cout << "\n";
}
