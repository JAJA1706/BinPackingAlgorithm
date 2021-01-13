#define BINPACK_
#ifndef BIPACK_

#include <list>

class BinPacking
{
public:
    static void mergeSort(float* array, unsigned size)
    {
        if (size == 0)
            return;

        mergeSortRec(array, 0, size - 1);
    }

    static int BestFit(float* array, unsigned size)
    {
        if (size == 0)
            return 0;
        mergeSort(array, size);
        std::list<float> containers;
        bool guard;
        for (unsigned i = 0; i < size; ++i)
        {
            if (array[i] > 1 || array[i] < 0)
            {
                return -1;
            }

            guard = false;
            for (std::list<float>::iterator it = containers.begin(); it != containers.end(); ++it)
            {
                if (*it + array[i] <= 1)
                {
                    *it += array[i];
                    guard = true;
                    break;
                }
            }
            if (!guard)
            {
                containers.push_back(array[i]);
            }
        }
        return containers.size();
    }
private:
    //Wersja nie in-place. Istnieje wersja in-place. Trzeba uzgodniæ czy taka nam starcza czy zmieniæ na in-place.
    static void merge(float* array, unsigned first, unsigned middle, unsigned last)
    {
        unsigned left_index = first;
        unsigned right_index = middle + 1;
        unsigned index = 0;
        float* temp = new float[last - first + 1]();

        while (left_index < middle + 1 || right_index < last + 1)
        {
            if (right_index == last + 1)
            {
                temp[index] = array[left_index];
                ++left_index;
            }
            else if (left_index == middle + 1)
            {
                temp[index] = array[right_index];
                ++right_index;
            }
            else if (array[left_index] > array[right_index])
            {
                temp[index] = array[left_index];
                ++left_index;
            }
            else
            {
                temp[index] = array[right_index];
                ++right_index;
            }
            ++index;
        }

        for (unsigned i = 0; i < (last - first + 1); ++i)
        {
            array[first + i] = temp[i];
        }
        delete[] temp;
    }

    static void mergeSortRec(float* array, unsigned first, unsigned last)
    {
        if (last > first)
        {
            unsigned middle = first + ((last - first) / 2);
            mergeSortRec(array, first, middle);
            mergeSortRec(array, middle + 1, last);
            merge(array, first, middle, last);
        }
    }

};

#endif // !BIPACK_
