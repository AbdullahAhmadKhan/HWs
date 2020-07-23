#include "Bank.h"

Bank :: Bank() {
  _bank_name = "not_defined";
  _user_count = 0;
  _users = nullptr;
}

Bank :: Bank(std::string bank_name, Account* const users, int user_count) {
  int i;
  _bank_name = bank_name;
  _user_count = user_count;
  _users = new Account[user_count];
  for (i = 0; i < _user_count; i++) {
    _users[i] = users[i];
  }
}

Bank :: ~Bank() {
  _bank_name = "";
  _user_count = 0;
  if (_users) {
    delete[] _users;
  }
}

Bank :: Bank(const Bank& rhs) {
  int i;
  _bank_name = rhs._bank_name;
  _user_count = rhs._user_count;
  _users = new Account[_user_count];
  for (i = 0; i < _user_count; i++) {
    _users[i] = rhs._users[i];
  }
}

int userInBank(Account user, int user_count, Account* users) {
  int i;
  for (i = 0; i < user_count; i++) {
    if (users[i] == user) {
      return i;
    }
  }
  return -1;
}

Bank& Bank :: operator+=(const Bank& rhs) {
  int i, index;
  std::string new_bank_name = _bank_name;
  int new_user_count = _user_count + rhs._user_count;
  Account* new_users = new Account[new_user_count];
  Bank* new_bank;

  for (i = 0; i < _user_count; i++) {
    Account* tempPtr = new Account(_users[i]);
    new_users[i] = *tempPtr;
    delete tempPtr;
  }
  for (i = _user_count; i < new_user_count; i++) {
    index = userInBank(rhs._users[i - _user_count], _user_count, _users);
    if (index == -1) {
      Account* tempPtr1 = new Account(rhs._users[i - _user_count]);
      new_users[i] = *tempPtr1;
      delete tempPtr1;
    }
    else {
      Account* tempPtr2 = new Account(rhs._users[i - _user_count] += _users[index]);
      new_users[i] = *tempPtr2;
      delete tempPtr2;
    }
  }

  this->~Bank();
  new_bank = new Bank(new_bank_name, new_users, new_user_count);
  *this = *new_bank;
  new_bank_name = "";
  new_user_count = 0;
  if (new_users) {
    delete[] new_users;
  }
  new_bank = nullptr;
  return *this;
}

Bank& Bank :: operator+=(const Account& new_acc) {
  int i, index;
  std::string new_bank_name = _bank_name;
  int new_user_count = _user_count + 1;
  Account* new_users;
  Bank* new_bank;

  index = userInBank(new_acc, _user_count, _users);
  if (index == -1) {
    new_users = new Account[new_user_count];
    for (i = 0; i < _user_count; i++) {
      Account* tempPtr = new Account(_users[i]);
      new_users[i] = *tempPtr;
      delete tempPtr;
    }
    new_users[_user_count] = new_acc;
  }
  else {
    new_users = new Account[_user_count];
    for (i = 0; i < _user_count; i++) {
      if (i != index){
        Account* tempPtr1 = new Account(_users[i]);
        new_users[i] = *tempPtr1;
        delete tempPtr1;
      }
      else {
        Account* tempPtr2 = new Account(_users[i] += new_acc);
        new_users[i] = *tempPtr2;
        delete tempPtr2;
      }
    }
  }

  this->~Bank();
  new_bank = new Bank(new_bank_name, new_users, new_user_count);
  *this = *new_bank;
  new_bank_name = "";
  new_user_count = 0;
  if (new_users) {
    delete[] new_users;
  }
  new_bank = nullptr;
  return *this;
}

Account& Bank :: operator[](int account_id) {
  int i;
  for (i = 0; i < _user_count; i++) {
    if (_users[i] == account_id) {
      return _users[i];
    }
  }
  return _users[0];
}

std::ostream& operator<<(std::ostream& os, const Bank& bank) {
  int bankBalance = 0, loanUsers = bank._user_count, i, j;
  struct tm t1, t2, t3;
  time_t time1, time2, time3;

  t1.tm_year = t2.tm_year = t3.tm_year = 119;
  t1.tm_mday = t2.tm_mday = t3.tm_mday = 01;
  t1.tm_hour = t2.tm_hour = t3.tm_hour = 00;
  t1.tm_min = t2.tm_min = t3.tm_min = 00;
  t1.tm_sec = t2.tm_sec = t3.tm_sec = 00;

  for (i = 0; i < bank._user_count; i++) {
    bankBalance += bank._users[i].balance();

    for (j = 0; j < 10; j++) {
      t1.tm_mon = j;
      t2.tm_mon = j + 1;
      t3.tm_mon = j + 2;

      time1 = mktime(&t1);
      time2 = mktime(&t2);
      time3 = mktime(&t3);

      if (bank._users[i].balance(time1, time2) < 0 && bank._users[i].balance(time2, time3) < 0) {
        loanUsers--;
        break;
      }
    }
  }

  os << bank._bank_name << "\t" << loanUsers << "\t" << bankBalance << "\n";
  return os;
}