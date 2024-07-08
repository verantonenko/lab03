#include <iostream>
#include <vector>

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers (size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
        cin >> result[i];

    return result;
}

void find_minmax(const vector<double> &numbers, double &min, double &max){
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

vector<size_t> make_histogram(const vector<double> &numbers, size_t &bin_count){

    vector<size_t> bins(bin_count);
    //определение диапозона чисел в массиве
    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    //определение индекса корзины по значению элемента
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((low <= numbers[i]) && (numbers[i] < high)) {
                bins[j]++;
                found = true;
            }
        }

        //когда numbers[i] = max
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogram_text(vector<size_t> bins){
    //находим наибольший столбец
    size_t max_count = bins[0];
    for (auto bin : bins){
        if (bin > max_count)
            max_count = bin;
    }

    // Масштабирование количества звездочек, если больше 76
    vector<size_t> bins_mash = bins;
    if (max_count > MAX_ASTERISK){
        for (size_t i = 0; i < bins.size(); i++) {
            size_t height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
            bins_mash[i] = height;
            //bins[i] = height;
        }
        max_count = bins_mash[0];
        for (auto bin : bins_mash){
            if (bin > max_count)
                max_count = bin;
        }
    }

    //выравнивание и вывод
    for (int i = 0; i < bins.size(); i++){
        if (bins[i] < 100)
            cout << ' ';
        if (bins[i] < 10)
            cout << ' ';
        cout << bins[i] << '|';

        for (int j = 0; j < bins_mash[i]; j++){
            cout << '*';
        }
        cout << endl;
    }
}

int main()
{
    size_t number_count;
    cerr << "enter number count: " << endl;
    cin >> number_count;

    cerr << "enter mas: " << endl;
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "enter bin count: " << endl;
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_text(bins);
}








/*#include <iostream>
#include <vector>

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(vector<double> numbers, double &min, double &max){
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
}

int main() {
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    // Обработка данных
    double min, max;
    find_minmax(numbers, min, max);

    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }

    // Вывод данных
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    const bool scaling_needed = max_count > MAX_ASTERISK;

    for (size_t bin : bins) {
        if (bin < 100) {
            cout << ' ';
        }
        if (bin < 10) {
            cout << ' ';
        }
        cout << bin << "|";

        size_t height = bin;
        if (scaling_needed) {
            const double scaling_factor = (double)MAX_ASTERISK / max_count;
            height = (size_t)(bin * scaling_factor);
        }

        for (size_t i = 0; i < height; i++) {
            cout << '*';
        }
        cout << '\n';
    }

    return 0;
}*/















/*vector<double> input_numbers (size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
        cin >> result[i];

    return result;
}

void find_minmax(const vector<double> &numbers, double &min, double &max){
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

vector<size_t> make_histogram(const vector<double> &numbers, size_t &bin_count){

    vector<size_t> bins(bin_count);
    //определение диапозона чисел в массиве
    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;

    //определение индекса корзины по значению элемента
    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((low <= numbers[i]) && (numbers[i] < high)) {
                bins[j]++;
                found = true;
            }
        }

        //когда numbers[i] = max
        if (!found) {
            bins[bin_count - 1]++;
        }
    }
    return bins;
}


void show_histogram_text(vector<size_t> bins){
    //находим наибольший столбец
    size_t max_count = bins[0];
    for (auto bin : bins){
        if (bin > max_count)
            max_count = bin;
    }

    // Масштабирование количества звездочек, если больше 76
    vector<size_t> bins_mash = bins;
    if (max_count > MAX_ASTERISK){
        for (size_t i = 0; i < bins.size(); i++) {
            size_t height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
            bins_mash[i] = height;
            //bins[i] = height;
        }
        max_count = bins_mash[0];
        for (auto bin : bins_mash){
            if (bin > max_count)
                max_count = bin;
        }
    }

    size_t interval;
    cerr << "enter interval: ";
    cin >> interval;

    if (interval < 4 || interval > 9){
        cerr << "ERROR";
        exit(0);
    }

    //выравнивание и вывод без масштабирования
    /*for (auto bin : bins){
        if (bin < 100)
            cout << ' ';
        if (bin < 10)
            cout << ' ';
        cout << bin << '|';

        for (int i = 0; i < bin; i++){
            cout << '*';
        }
        cout << endl;
    }


    //выравнивание и вывод
    for (int i = 0; i < bins.size(); i++){
        if (bins[i] < 100)
            cout << ' ';
        if (bins[i] < 10)
            cout << ' ';
        cout << bins[i] << '|';

        for (int j = 0; j < bins_mash[i]; j++){
            cout << '*';
        }
        cout << endl;
    }

    //вывод шкалы

    int border = (max_count / interval) + 1;
    cout << "   ";
    for (int i = 0; i < border; i++){
        cout << "|";
        for (int j = 1; j < interval; j++){
            cout << '-';
        }
    }

    //вывод циферок шкалы
    cout << '|' << endl << "   ";
    for (int i = 0; i <= border; i++){
        if (i == 0 || i == 1 || i == border) {
            cout << i * interval;
            for (int j = 1; j < interval; j++){
                cout << ' ';
            }
        }
        else{
            cout << ' ';
            for (int j = 1; j < interval; j++){
                cout << ' ';
            }
        }
    }
}


void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void svg_end() {
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins) {
    svg_begin(400, 300);
    svg_end();
}*/
