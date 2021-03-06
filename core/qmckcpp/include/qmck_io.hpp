#include <qmck.hpp>
#include <ostream>

std::ostream &operator<<(std::ostream &out, const qmck::quine_row &lhs);

std::ostream &operator<<(std::ostream &out, const qmck::quine_table &lhs);

std::ostream &operator<<(std::ostream &out, const qmck::logic_row &lhs);

std::ostream &operator<<(std::ostream &out, const qmck::logic_table &lhs);

std::ostream &operator<<(std::ostream &out, const qmck::generic_table_format &lhs);

std::ostream &operator<<(std::ostream &out, const qmck::result_table &lhs);

void print_result_row(std::ostream &out, const qmck::result_row &row, const qmck::generic_table_format &format);
