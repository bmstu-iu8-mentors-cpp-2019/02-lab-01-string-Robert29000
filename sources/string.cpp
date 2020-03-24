//Copyright 2020 Robert

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <memory.h>
#include <string.hpp>

String::~String(){
 delete[] Data;
}

String::String(){
 Data = nullptr;
}

String::String(const String& rhs):String(rhs.Data)
{}

String::String(const char* data){
 size_t length = std::strlen(data);
 Data = new char[length+1];
 Data[length] = '\0';
 for (size_t i = 0; i < length; i++){
  std::copy(Data[i], data[i]);
 }
}

String& String::operator=(const String& rhs){
 if (&rhs != this){
 delete [] Data;
 size_t length = rhs.Size();
 Data = new char[length+1];
 Data[length] = '\0';
  for (size_t i = 0 ; i < length ; i++){
   std::copy(Data[i], rhs.Data[i]);
  }
 }
 return *this;
}

String& String::operator+=(const String& rhs){
 (*this) = (*this) + rhs;
 return *this;
}

String& String::operator+=(const char* substr){
 String rhs(substr);
 (*this) = (*this) + rhs;
 return *this;
}

String& String::operator*=(unsigned int m){
 (*this) = (*this) * m;
 return *this;
}

bool String::operator==(const String& rhs) const{
 for (size_t i = 0 ; i < Size() ; i++){
  if (Data[i] != rhs[i]){
   return false;
  }
 }
 return true;
}

bool operator==(const char* lhs, const String& rhs){
 String sLhs(lhs);
 return sLhs == rhs;
}

bool String::operator<(const String& rhs) const{
 for (size_t i = 0 ; i < Size(); i++){
  if (Data[i] < rhs[i]){
   return true;
  }else if (Data[i] == rhs[i]){
   continue;
  }else{
   return false;
  }
 }
 return false;
}

size_t String::Find(const String& substr) const{
 size_t word_length = substr.Size();
 for (size_t i = 0; i < Size() - word_length + 1; ++i) {
  if (std::equal(Data[i], Data[i] + word_length, substr.Data)) {
   return i;
  }
 }
 return std::string::npos;
}

size_t String::Find(const char* substr) const{
 String data(substr);
 return Find(data);
}

void String::Replace(char oldSymbol, char newSymbol){
 for (size_t i = 0 ; i < Size(); i++){
  if (Data[i] == oldSymbol){
   Data[i] = newSymbol;
  }
 }
}

size_t String::Size() const{
 if (Data != nullptr){
  return std::strlen(Data);
 }else{
  return 0;
 }
}

bool String::Empty() const{
 return Size() == 0;
}

char String::operator[](size_t index) const{
 return Data[index];
}

char& String::operator[](size_t index){
 return Data[index];
}

void String::RTrim(char symbol){
 int count = 0;
 for (size_t i = Size() - 1; i != 0; i--){
  if (Data[i] == symbol){
   count++;
  }else{
   break;
  }
 }
 size_t newLen = Size() - count;
 char *data = new char[newLen+1];
 data[newLen] = '\0';
 int hCount = 0;
 for (size_t i = 0; i < Size(); i++){
  if (Data[i] != symbol || hCount == count){
   data[i] = Data[i];
  }else{
   hCount++;
  }
 }
 delete[] Data;
 Data = data;
}

void String::LTrim(char symbol){
 int count = 0;
 for (size_t i = 0; i < Size(); i++){
  if (Data[i] == symbol){
   count++;
  }else{
   break;
  }
 }
 size_t newLen = Size() - count;
 char *data = new char[newLen+1];
 data[newLen] = '\0';
 int hCount = 0;
 for (size_t i = 0; i < Size(); i++){
  if (Data[i] != symbol || hCount == count){
   data[i-count] = Data[i];
  }else{
   hCount++;
  }
 }
 delete[] Data;
 Data = data;
}

void String::swap(String& oth){
 std::swap(Data, oth.Data);
}

String operator+(const String& a, const String& b){
 size_t length = a.Size() + b.Size();
 char *data = new char[length+1];
 data[length] = '\0';
 for (size_t i = 0; i < length; i++){
  if (i < a.Size()){
   data[i] = a[i];
  }else{
   data[i] = b[i - a.Size()];
  }
 }
 String res(data);
 delete[] data;
 return res;
}

String operator*(const String& a, unsigned int b){
 size_t length = a.Size() * (b+1);
 char* data = new char[length+1];
 data[length] = '\0';
 int counter = 0;
 for (size_t j = 0; j <= b ; j++){
  for (size_t i = 0; i < a.Size(); i++){
   data[counter] = a[i];
   counter++;
  }
 }
 String res(data);
 delete[] data;
 return res;
}

std::ostream& operator<<(std::ostream& out, const String& str){
 return out str.Data;
}
