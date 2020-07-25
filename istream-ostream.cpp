
// you need to include at least on arg as ostream or istream to be able to create your new operator(from where do you want to take your info?)
ostream& operator<<(ostream& out, const argument){ // & - is necessary to be able to continue printing out 
  return out;
}
istream& operator>>(istream& in, type& arg){
int num_rows, num_columns;
    in >> num_rows >> num_columns;
  return in
}
