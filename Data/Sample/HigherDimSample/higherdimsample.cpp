#include "higherdimsample.h"

HigherDimSample::HigherDimSample(const QList<QList<double>> &one_dim_values) : one_dim_values(one_dim_values), correlation_matrix()
{
    for(int j = 0; j < this->one_dim_values.size();j ++){
        double x_average = Parameter::Average(this->one_dim_values[j]);
        double x_disp = Parameter::Dispersion(this->one_dim_values[j]);
        for(int i = 0; i < one_dim_values[j].size(); i++){
            this->one_dim_values[j][i] = one_dim_values[j][i];
        }
        one_dim_samples.append(new OneDimSample("wanna know how i get those scars?", this->one_dim_values[j]));
        one_dim_samples.last()->PrimaryAnalysis();
    }
}

void HigherDimSample::PrimaryAnalysis()
{
    higher_dim_variation = SetVariation();
    correlation_matrix = SetCorrelationMatrix();
}

QList<QList<Variation*> > HigherDimSample::SetVariation()
{
    int size_samples = 0;
    double just_for_lulz = 0;
    QList<QList<Variation*>> variation = QList<QList<Variation*>>();
    foreach(OneDimSample *el, one_dim_samples)
        size_samples += el->sample.size();
    foreach(OneDimSample *el, one_dim_samples){
        QList<Variation*> el_variation = QList<Variation*>();
        foreach(Variation *el_2, el->variation){
            el_variation.append(new Variation(el_2->x, el_2->n, (double)(el_2->n) / (double)(size_samples)));
            just_for_lulz += el_variation.last()->p;
        }
        variation.append(el_variation);
    }
    return variation;
}

QList<QList<double>> HigherDimSample::SetCorrelationMatrix()
{
    QList<QList<double>> matrix = QList<QList<double>>();
    foreach(OneDimSample *el, one_dim_samples){
        QList<double> matrix_row = QList<double>();
        foreach(OneDimSample *el_2, one_dim_samples){
            if(el == el_2)
                matrix_row.append(1);
            else
                matrix_row.append(TwoDimParameter::CorrelationCoefficient(*el, *el_2));
        }
        matrix.append(matrix_row);
    }
    return matrix;
}

TwoDimParameter *HigherDimSample::SetPartial(const QList<QList<double> > &matrix, const int &index_i, const int &index_j, const QList<int> &index_c)
{
    double value = GetPartial(matrix, index_i, index_j, index_c);

    QString val_string = "Частковий коефіцієнт корреляції між " + QString(index_i) + ", " + QString(index_j) + " * c";
    double n = matrix.size() * matrix.size();
    double t = value * sqrt(n - index_c.size() - 2) / sqrt(1 - pow(value, 2.0));
    double t_quantile = Quantile::TQuantile(0.9, n - index_c.size() - 2);
    double u_quantile = Quantile::UQuantile(0.1);

    double v1 = 0.5 * log((1 + value) / (1 - value)) - u_quantile / (n - index_c.size() - 3);
    double v2 = 0.5 * log((1 + value) / (1 - value)) + u_quantile / (n - index_c.size() - 3);
    double upper_border = (exp(2 * v2) - 1) / (exp(2 * v2) + 1);
    double lower_border = (exp(2 * v1) - 1) / (exp(2 * v1) + 1);

    return new TwoDimParameter(val_string, value, t , abs(t) > t_quantile, lower_border, upper_border, t_quantile);
}

double HigherDimSample::GetPartial(const QList<QList<double>> &matrix, const int &index_i, const int &index_j, const QList<int> &index_c)
{
    if(index_c.size() == 1)
        return GetPartial(matrix, index_i, index_j, index_c[0]);
    double answer = 0;
    QList<int> new_list;
    for(int i = 1; i < index_c.size(); i++){
        new_list << index_c[i];
    }
    double r_upper_first = GetPartial(matrix, index_i, index_j, new_list);
    double r_upper_second = GetPartial(matrix, index_i, index_c[0], new_list);
    double r_upper_third = GetPartial(matrix, index_j, index_c[0], new_list);
    return (r_upper_first - r_upper_second * r_upper_third) / sqrt((1 - pow(r_upper_second, 2.0)) * (1 - pow(r_upper_third, 2.0)));
}

double HigherDimSample::GetPartial(const QList<QList<double>> &matrix, const int &index_i, const int &index_j, const int &index_d)
{
    double f1 = matrix[index_i][index_j] - matrix[index_i][index_d] * matrix[index_j][index_d];
    double f2 = (1 - pow(matrix[index_i][index_d], 2.0)) * (1 - pow(matrix[index_j][index_d], 2.0));
    return f1/sqrt(f2);
}

TwoDimParameter *HigherDimSample::SetMultiple(const QList<QList<double> > &matrix, const int &index_i, const int &index_j)
{
    double value = GetMultiple(matrix, index_i, index_j);

    QString val_string = "Множинний коефіцієнт корреляції між " + QString(index_i) + ", " + QString(index_j);
    double n = matrix.size() * matrix.size();
    double f = 0;
    double f_quantile = Quantile::FQuantile(0, 0, 0);
    double u_quantile = Quantile::UQuantile(0.1);

    return new TwoDimParameter(val_string, value, f , abs(f) > f_quantile, 0, 0, f_quantile);
}

double HigherDimSample::GetMultiple(const QList<QList<double> > &matrix, const int &index_i, const int &index_j)
{
    return sqrt(1 - Determinant(matrix) / Determinant(matrix, index_i, index_j));
}

double HigherDimSample::Determinant(const QList<QList<double> > &matrix, const int &index_i, const int &index_j)
{
    QList<QList<double>> new_matrix;
    if(index_i != -1 && index_j != -1){
        for(int i = 0; i < matrix.size(); i++){
            if(i == index_i)
                continue;
            QList<double> val_matrix;
            for(int j = 0; j < matrix.size(); j++){
                if(j == index_j)
                    continue;
                val_matrix.append(matrix[i][j]);
            }
            new_matrix.append(val_matrix);
        }
    }
    else{
        new_matrix = matrix;
    }
    if(new_matrix.size() <= 0)
        return 0;
    if(new_matrix.size() == 1)
        return new_matrix[0][0];
    if(new_matrix.size() == 2){
        return new_matrix[0][0] * new_matrix[1][1] - new_matrix[0][1] * new_matrix[1][0];
    }
    double matrix_determinant = 0;
    for(int i = 0; i < new_matrix.size(); i++){
        double det_matrix = Determinant(new_matrix, 0, i);
        double mat_value = new_matrix[0][i];
        matrix_determinant += pow(-1, i) * mat_value * det_matrix;
    }
    return matrix_determinant;
}

int HigherDimSample::RowSize() const
{
    return one_dim_samples.size();
}

const QString HigherDimSample::GetName() const
{
    return "you know something about me?";
}

const QVariant HigherDimSample::ShowInfo(const int &chosenInfo) const
{
    return "da";
}

int HigherDimSample::GetSampleType() const
{
    return 13;
}

void *HigherDimSample::GetChild(const int &childId)
{
    return one_dim_samples[childId];
}
