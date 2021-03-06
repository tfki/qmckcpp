#include <qmck_io.hpp>

std::ostream &operator<<(std::ostream &out, const qmck::quine_row &lhs)
{
    return out;
}

std::ostream &operator<<(std::ostream &out, const qmck::quine_table &lhs)
{
    out << "qmck::quine_table {\n";
    out << "generic_table_format=" << lhs.format << ",\n\n";
    out << "----------------\n";

    for (size_t bundle_i = 0; bundle_i < lhs.ranks.size(); ++bundle_i)
    {
        auto const &current_bundle = lhs.ranks[bundle_i];
        if (!current_bundle.empty())
        {
            for (const auto &row_i : current_bundle)
            {
                for (uint32_t j = 0; j < lhs.format.inputs_count; ++j)
                {
                    if ((row_i.inputs_deduced_mask >> (lhs.format.inputs_count - j - 1)) & 1u)
                    {
                        out << 'X';
                    }
                    else
                    {
                        out << (((row_i.inputs >> (lhs.format.inputs_count - j - 1)) & 1u) ? '1' : '0');
                    }
                }
                out << " | ";

                for (uint32_t k = 0; k < lhs.format.outputs_count; ++k)
                {
                    out << (((row_i.outputs >> (lhs.format.outputs_count - k - 1)) & 1u) ? '1' : '0');
                }
                out << "  ";

                for (uint32_t l = 0; l < lhs.format.outputs_count; ++l)
                {
                    out << (((row_i.outputs_done_mask >> (lhs.format.outputs_count - l - 1)) & 1u) ? '1' : '0');
                }

                if ((row_i.outputs_done_mask & row_i.outputs) == row_i.outputs)
                {
                    out << " (covered) ";
                }
                else
                {
                    out << " (not covered) ";
                }

                auto minterms_covered = row_i.calculate_minterms_covered();
                for (auto &minterm : minterms_covered)
                {
                    out << minterm << ',';
                }

                out << '\n';
            }
            out << "----------------\n";
        }
    }

    out << '}';
    return out;
}

std::ostream &operator<<(std::ostream &out, const qmck::logic_row &lhs)
{
    return out;
}

std::ostream &operator<<(std::ostream &out, const qmck::logic_table &lhs)
{
    out << "qmck::logic_table{\n";
    out << "generic_table_format=" << lhs.format << ",\n\n";

    for (size_t i = 0; i < lhs.rows.size(); ++i)
    {
        for (uint32_t j = 0; j < lhs.format.inputs_count; ++j)
        {
            out << (((lhs.rows[i].inputs >> (lhs.format.inputs_count - j - 1)) & 1u) ? '1' : '0');
        }
        out << " | ";

        for (uint32_t k = 0; k < lhs.format.outputs_count; ++k)
        {
            out << (((lhs.rows[i].outputs >> (lhs.format.outputs_count - k - 1)) & 1u) ? '1' : '0');
        }
        out << "  ";

        for (uint32_t l = 0; l < lhs.format.outputs_count; ++l)
        {
            out << (((lhs.rows[i].outputs_dc_mask >> (lhs.format.outputs_count - l - 1)) & 1u) ? '1' : '0');
        }
        out << '\n';
    }

    out << "}";
    return out;
}

std::ostream &operator<<(std::ostream &out, const qmck::generic_table_format &lhs)
{
    // + is necessary because uint8_t is typedeffed a uchar and treated as such by ostream
    out << "qmck::table_format{inputs_count=" << +lhs.inputs_count << ", outputs_count=" << +lhs.outputs_count << "}";
    return out;
}

std::ostream &operator<<(std::ostream &out, const qmck::result_table &lhs)
{
    out << "qmck::result_table {\n";
    out << "generic_table_format=" << lhs.format << ",\n\n";

    for (auto pair:lhs.rows)
    {
        auto &quine_row = pair.second;
        auto &id = pair.first;

        out << "id:" << id << "  ";

        for (uint32_t j = 0; j < lhs.format.inputs_count; ++j)
        {
            if ((quine_row.inputs_deduced_mask >> (lhs.format.inputs_count - j - 1)) & 1u)
            {
                out << 'X';
            }
            else
            {
                out << (((quine_row.inputs >> (lhs.format.inputs_count - j - 1)) & 1u) ? '1' : '0');
            }
        }
        out << " | ";

        for (uint32_t k = 0; k < lhs.format.outputs_count; ++k)
        {
            out << (((quine_row.outputs >> (lhs.format.outputs_count - k - 1)) & 1u) ? '1' : '0');
        }
        out << "  ";

        auto minterms_covered = quine_row.calculate_minterms_covered();
        for (auto &minterm : minterms_covered)
        {
            out << minterm << ',';
        }

        out << "\n";
    }

    out << '}';
    return out;
}

void print_result_row(std::ostream &out, const qmck::result_row &row, const qmck::generic_table_format &format)
{
    char variable = 'a';
    for (uint32_t j = 0; j < format.inputs_count; ++j)
    {
        if (!((row.inputs_deduced_mask >> (format.inputs_count - j - 1)) & 1u))
        {
            out << variable;
            if (!((row.inputs >> (format.inputs_count - j - 1)) & 1u))
            {
                out << '\'';
            }
            out << '*';
        }
        ++variable;
    }
    // override trailing * with space
    out << "\b ";
}
