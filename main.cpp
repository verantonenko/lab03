#include <iostream>
#include <vector>
#include "histogram.h"

using namespace std;

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;

vector<double> input_numbers (size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
        cin >> result[i];

    return result;
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


/*void show_histogram_text(vector<size_t> bins){
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
}*/

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

void svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black"){
    cout << "<rect x='" << x << "' y='" << y
         << "' width='" << width << "' height='" << height << "' />\n";
         //<< "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}

void show_histogram_svg(const vector<size_t>& bins) {

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    //моё масштабирование svg
    //находим наибольший столбец
    size_t max_count = bins[0];
    for (auto bin : bins){
        if (bin > max_count)
            max_count = bin;
    }

    // Масштабирование количества звездочек
    vector<size_t> bins_mash = bins;
    if ((max_count * BLOCK_WIDTH) > (IMAGE_WIDTH - TEXT_WIDTH)){
        for (size_t i = 0; i < bins.size(); i++) {
            size_t height = MAX_ASTERISK * (static_cast<double>(bins[i]) / max_count);
            bins_mash[i] = height;
        }
    }

    //вывод гистограмы в svg
    double top = 0;
    for (size_t i = 0; i < bins_mash.size(); i++) {
        const double bin_width = BLOCK_WIDTH * bins_mash[i];
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT); //"deeppink", "#FF69B4"
        top += BIN_HEIGHT;
    }
    svg_end();
}

int main()
{
    size_t number_count;
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    show_histogram_svg(bins);
}
