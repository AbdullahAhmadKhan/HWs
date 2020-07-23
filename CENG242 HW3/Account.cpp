#include "Account.h"

Account :: Account() {
  _id = -1;
  _activity = nullptr;
  _monthly_activity_frequency = nullptr;
}

Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency) {
  int m, l, p, i, j, k, n;
  _id = id;
  if (monthly_activity_frequency) {
    _monthly_activity_frequency = new int[12]{};
    for (l = 0; l < 12; l++) {
      _monthly_activity_frequency[l] = monthly_activity_frequency[l];
    }
  }

  if (activity) {
    _activity = new Transaction*[12]{};
    for (l = 0; l < 12; l++)  {
      m = monthly_activity_frequency[l];
      if (m) {
        _activity[l] = new Transaction[m]{};
        for (p = 0; p < m; p++) {
          Transaction* tempPtr = new Transaction(activity[l][p]);
          _activity[l][p] = *tempPtr;
          delete tempPtr;
        }
      }
      else {
        _activity[l] = nullptr;
      }
    }
  }
  
  Transaction temp;
  Transaction* x;
  Transaction* y;
  for (i = 0; i < 12; i++) {
    n = _monthly_activity_frequency[i];
    for (j = 0; j < n - 1; j++) {
      for (k = 0; k < n - j - 1; k++) {
        if (_activity[i][k] > _activity[i][k + 1]) {
          x = &_activity[i][k];
          y = &_activity[i][k + 1];
          temp = *x;
          *x = *y;
          *y = temp;
        }
      }
    }
  }
}

Account :: ~Account() {
  _id = 0;
  if (_monthly_activity_frequency) {
    delete[] _monthly_activity_frequency;
  }
  if (_activity) {
    for (int i = 0; i < 12; i++) {
      delete[] _activity[i];
    }
    delete[] _activity;
  }
}

Account :: Account(const Account& rhs) {
  int n, i, j;
  _id = rhs._id;
  if (rhs._monthly_activity_frequency) {
    _monthly_activity_frequency = new int[12]{};
    for (i = 0; i < 12; i++) {
      _monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }
  }

  if (rhs._activity) {
    _activity = new Transaction*[12]{};
    for (i = 0; i < 12; i++) {
      n = rhs._monthly_activity_frequency[i];
      if (n) {
        _activity[i] = new Transaction[n]{};
        for (j = 0; j < n; j++) {
          Transaction* tempPtr = new Transaction(rhs._activity[i][j]);
          _activity[i][j] = *tempPtr;
          delete tempPtr;
        }
      }
      else {
        _activity[i] = nullptr;
      }
    }
  }
}

Account :: Account(const Account& rhs, time_t start_date, time_t end_date) {
  int n, m, i, j, k;
  _id = rhs._id;
  if (rhs._monthly_activity_frequency) {
    _monthly_activity_frequency = new int[12]{};
    for (i = 0; i < 12; i++) {
      _monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }
  }
  if (rhs._activity) {
    _activity = new Transaction*[12]{};
    for (i = 0; i < 12; i++) {
      m = rhs._monthly_activity_frequency[i];
      if (m) {
        n = 1;
        for (j = 0; j < m; j++) {
          if (rhs._activity[i][j] > start_date && rhs._activity[i][j] < end_date) {
            n++;
          }
        }
        if (n-1) {
            _activity[i] = new Transaction[n]{};
            k = 0;
            for (j = 0; j < m; j++) {
              if (rhs._activity[i][j] > start_date && rhs._activity[i][j] < end_date) {
                Transaction* tempPtr = new Transaction(rhs._activity[i][j]);
                _activity[i][k] = *tempPtr;
                delete tempPtr;
                k++;
              }
              else {
                _monthly_activity_frequency[i] -= 1;
              }
            }
        }
        else {
          _monthly_activity_frequency[i] = 0;
          _activity[i] = nullptr;
        }
      }
      else {
        _activity[i] = nullptr;
      }
    }
  }
}

Account :: Account(Account&& rhs) : _id(0), _monthly_activity_frequency(nullptr), _activity(nullptr) {
  std::swap(_id, rhs._id);
  std::swap(_monthly_activity_frequency, rhs._monthly_activity_frequency);
  std::swap(_activity, rhs._activity);
}

Account& Account :: operator=(Account&& rhs) {
  std::swap(*this, rhs);
  return *this;
}

Account& Account :: operator=(const Account& rhs) {
  int n, i, j;
  _id = rhs._id;
  if (rhs._monthly_activity_frequency) {
    this->_monthly_activity_frequency = new int[12]{};
    for (i = 0; i < 12; i++) {
      this->_monthly_activity_frequency[i] = rhs._monthly_activity_frequency[i];
    }
  }

  if (rhs._activity) {
    this->_activity = new Transaction*[12]{};
    for (i = 0; i < 12; i++) {
      n = rhs._monthly_activity_frequency[i];
      if (n) {
        this->_activity[i] = new Transaction[n]{};
        for (j = 0; j < n; j++) {
          Transaction* tempPtr = new Transaction(rhs._activity[i][j]);
          this->_activity[i][j] = *tempPtr;
          delete tempPtr;
        }
      }
      else {
        this->_activity[i] = nullptr;
      }
    }
  }

  return *this;
}

bool Account :: operator==(const Account& rhs) const {
  if (_id == rhs._id) {
    return true;
  }
  return false;
}

bool Account :: operator==(int id) const {
  if (_id == id) {
    return true;
  }
  return false;
}

Account& Account :: operator+=(const Account& rhs) {
  int n, m, i, j, k, new_id = this->_id;
  Transaction** new_activity = new Transaction*[12]{};
  int* new_monthly_activity_frequency = new int[12]{};
  Account* new_account;
  Transaction temp;
  Transaction* x;
  Transaction* y;

  for (i = 0; i < 12; i++) {
    new_monthly_activity_frequency[i] = _monthly_activity_frequency[i] + rhs._monthly_activity_frequency[i];
  }
  for (i = 0; i < 12; i++) {
    n = _monthly_activity_frequency[i];
    m = rhs._monthly_activity_frequency[i];
    if (n + m) {
      new_activity[i] = new Transaction[n + m]{};
      for (j = 0; j < n; j++) {
        Transaction* tempPtr = new Transaction(_activity[i][j]);
        new_activity[i][j] = *tempPtr;
        delete tempPtr;
      }
      for (j = n; j < m + n; j++) {
        Transaction* tempPtr1 = new Transaction(rhs._activity[i][j - n]);
        new_activity[i][j] = *tempPtr1;
        delete tempPtr1;
      }
    }
    else {
      new_activity[i] = nullptr;
    }
  }

  for (i = 0; i < 12; i++) {
    n = new_monthly_activity_frequency[i];
    for (j = 0; j < n - 1; j++) {
      for (k = 0; k < n - j - 1; k++) {
        if (new_activity[i][k] > new_activity[i][k + 1]) {
          x = &new_activity[i][k];
          y = &new_activity[i][k + 1];
          temp = *x;
          *x = *y;
          *y = temp;
        }
      }
    }
  }

  this->~Account();
  new_account = new Account(new_id, new_activity, new_monthly_activity_frequency);
  *this = *new_account;
  new_account->~Account();
  new_id = 0;
  if (new_monthly_activity_frequency) {
    delete[] new_monthly_activity_frequency;
  }
  if (new_activity) {
    for (int i = 0; i < 12; i++) {
      delete[] new_activity[i];
    }
    delete[] new_activity;
  }
  new_account = nullptr;

  return *this;
}

double Account :: balance() {
  int i, j, n;
  double accountBalance = 0.0;
  for (i = 0; i < 12; i++) {
    n = _monthly_activity_frequency[i];
    for (j = 0; j < n; j++) {
      accountBalance = _activity[i][j] + accountBalance;
    }
  }
  return accountBalance;
}

double Account :: balance(time_t end_date) {
  int i, j, n;
  double accountBalance = 0.0;
  for (i = 0; i < 12; i++) {
    n = _monthly_activity_frequency[i];
    for (j = 0; j < n; j++) {
      if (_activity[i][j] < end_date) {
        accountBalance = _activity[i][j] + accountBalance;
      }
    }
  }
  return accountBalance;
}

double Account :: balance(time_t start_date, time_t end_date) {
  int i, j, n;
  double accountBalance = 0.0;
  for (i = 0; i < 12; i++) {
    n = _monthly_activity_frequency[i];
    for (j = 0; j < n; j++) {
      if (_activity[i][j] > start_date && _activity[i][j] < end_date) {
        accountBalance = _activity[i][j] + accountBalance;
      }
    }
  }
  return accountBalance;
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
  int n, i, j;
  if (!account._activity || !account._monthly_activity_frequency) {
    os << -1 << "\n";
    return os;
  }
  os << account._id << "\n";
  for (i = 0; i < 12; i++) {
    n = account._monthly_activity_frequency[i];
    for (j = 0; j < n; j++) {
    os << account._activity[i][j];
    }
  }

  return os;
}