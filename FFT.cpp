#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <complex>
#include <algorithm>
#include <iomanip>
#include <complex>
#include <initializer_list>
using namespace std;

template <typename T>
T GetRoot(int degree) {
    const long double argument = 2*M_PI/degree;
    T root_of_unity (cos(argument), sin(argument));
    if(abs(root_of_unity.real()) < pow(10, -5)){
        root_of_unity.real(0);
    }
    if(abs(root_of_unity.imag()) < pow(10, -5)){
        root_of_unity.imag(0);
    }
    return root_of_unity;
};

template <typename T>
vector<T> AddPadding(const std::vector<T>& data, size_t expected_length){
    if(expected_length < data.size()){
        throw runtime_error("Expexted length is too small!");
        return data;
    }
    vector<T> data_edited = data;
    data_edited.resize(expected_length, 0);
    return data_edited;
};

template <typename T>
vector<T> FastFourierTransform(const std::vector<T>& data){
    std::vector<T> data_edited = data;
    int size = data_edited.size();
	if (size == 1)  return data_edited;

    vector<T> data_0(size/2),  data_1(size/2);
	for (int i=0, j=0; i < size; i+=2, j++) {
		data_0[j] = data_edited[i];
		data_1[j] = data_edited[i+1];
	}
	data_0 = FastFourierTransform(data_0);
	data_1 = FastFourierTransform(data_1);

    T root(1);
    T root_of_unity = GetRoot<T>(size);
    cout << "size = " << size << endl;
    for(auto e: data_0){
        cout << e;
    };
    cout << endl;
    for(auto e: data_1){
        cout << e;
    };
    cout << endl;
    for(int i = 0; i < (size/2); i++){
        data_edited[i] = data_0[i] + root*data_1[i];
        if(abs(data_edited[i].real()) < 1e-5){
            data_edited[i].real(0);
        }
        if(abs(data_edited[i].imag()) < 1e-5){
            data_edited[i].imag(0);
        }
        cout << "[i] = " << i << ": " << data_0[i] << " + " << root << "*" << data_1[i] << "="<< data_edited[i] << endl;
        data_edited[i + (size/2)] = data_0[i] - root*data_1[i];
        if(abs(data_edited[i + (size/2)].real()) < 1e-5){
            data_edited[i + (size/2)].real(0);
        }
        if(abs(data_edited[i + (size/2)].imag()) < 1e-5){
            data_edited[i + (size/2)].imag(0);
        }
        root *= root_of_unity;
        cout << "[i + (size/2)] = " << i + (size/2) << ": " << data_0[i] << " - " << root << "*" << data_1[i] << "="<< data_edited[i + (size/2)] << endl;
        /*if(abs(root.real()) < 1e-5){
            root.real(0);
        }
        if(abs(root.imag()) < 1e-5){
            root.imag(0);
        }*/
    }
    return data_edited;
};

template <typename T>
vector<T> FastInverseFourierTransform(const std::vector<T>& data){
    std::vector<T> data_edited = data;
    int size = data_edited.size();
	if (size == 1)  return data_edited;

    vector<T> data_0(size/2),  data_1(size/2);
	for (int i=0, j=0; i < size; i+=2, j++) {
		data_0[j] = data_edited[i];
		data_1[j] = data_edited[i+1];
	}
	data_0 = FastInverseFourierTransform(data_0);
	data_1 = FastInverseFourierTransform(data_1);

    T root(1);
    T root_of_unity = GetRoot<T>(-size);
    cout << "size = " << size << endl;
    for(auto e: data_0){
        cout << e;
    };
    cout << endl;
    for(auto e: data_1){
        cout << e;
    };
    cout << endl;
    for(int i = 0; i < (size/2); i++){
        data_edited[i] = data_0[i] + root*data_1[i];
        data_edited[i] /= 2;
        if(abs(data_edited[i].real()) < 1e-5){
            data_edited[i].real(0);
        }
        if(abs(data_edited[i].imag()) < 1e-5){
            data_edited[i].imag(0);
        }
        cout << "[i] = " << i << ": " << data_0[i] << " + " << root << "*" << data_1[i] << "=2*"<< data_edited[i] << endl;
        data_edited[i + (size/2)] = data_0[i] - root*data_1[i];       
        data_edited[i + (size/2)] /= 2;
        if(abs(data_edited[i + (size/2)].real()) < 1e-5){
            data_edited[i + (size/2)].real(0);
        }
        if(abs(data_edited[i + (size/2)].imag()) < 1e-5){
            data_edited[i + (size/2)].imag(0);
        }
        cout << "[i + (size/2)] = " << i + (size/2) << ": " << data_0[i] << " - " << root << "*" << data_1[i] << "=2*"<< data_edited[i + (size/2)] << endl;
        root *= root_of_unity;
        /*if(abs(root.real()) < 1e-5){
            root.real(0);
        }
        if(abs(root.imag()) < 1e-5){
            root.imag(0);
        }*/
    }
    
    return data_edited;
};

template <typename T>
vector<T> FourierTransform(const std::vector<T>& data){
    int data_size = data.size(), power = 1;
    while(power < data_size){
        power *=2;
    };
    vector<T> data_edited = AddPadding(data, power);
    cout << "FFT:";
    for(auto e: data_edited){
        cout << e;
    };
    cout << endl;
    vector<T> transformed_by_Furie_data = FastFourierTransform(data_edited);
    return transformed_by_Furie_data;
};

template <typename T>
vector<T> InverseFourierTransform(const std::vector<T>& data){
    vector<T> transformed_by_Furie_data = data;
    int data_size = transformed_by_Furie_data.size(), power = 1;
    while(power < data_size){
        power *=2;
    };
    vector<T> data_edited = AddPadding(transformed_by_Furie_data, power);    
    cout << "FIFT:";
    for(auto e: data_edited){
        cout << e;
    };
    cout << endl;
    vector<T> normal_data = FastInverseFourierTransform(data_edited);
    return normal_data;
};

int main(void) {
    vector<complex<double>> data_1{1, 2, 0, 3};
    vector<complex<double>> data_edited_1= FourierTransform(data_1);
    for(auto e: data_edited_1){
        cout << e;
    };
    cout << endl << "--------------------------------------------------------" << endl;
    vector<complex<double>> data_2{1, 1, 1, 1};
    vector<complex<double>> data_edited_2= FourierTransform(data_2);
    for(auto e: data_edited_2){
        cout << e;
    };
    cout << endl << "--------------------------------------------------------" << endl;
    int vector_size = max(data_edited_1.size(), data_edited_1.size());
    cout << vector_size << endl;
    vector<complex<double>> data_edited(vector_size);
    for (int i = 0; i < vector_size; i++) {
        data_edited[i] = data_edited_1[i] * data_edited_2[i];
    }
    vector<complex<double>> data = InverseFourierTransform(data_edited);
    for(const auto& e: data) {
        cout << e;
    }
    cout << endl;
}