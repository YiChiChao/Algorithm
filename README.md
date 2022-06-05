# Sorting Note 
[TOC]
## 時間複雜度
Def: 當輸入n筆資料時，此function所需要花費的時間。通常指最差情況複雜度(就是在最衰的情況，同一種輸入所需要花最長的時間)
### Upper Bound Bound -> Worst Case($O(f(n)$)
$def$：$T(n)$ $=$ $O(f(n))$ if and only if there exist two positive constants c
and n0 such that $T(n)$ $≤$ $cf(n)$ for all $n$ $≥$ $n_0$.
>解釋：
>T(n)是一個演算法實際隨著n變大而成長的線，f(n)算是一條上界，可以是1、n、n^2、logn...。
>只要上下移動這條上界到可以使這條上界永遠大於T(n)這條線，那f(n)就可以是T(n)的upper bound.

在看Worst Case 的時候，就是在看當n到無限大的時候，這個演算法最慢需要多少時間，所以用的是Upper Bound

### Lower Bound -> Best Case
在討論Best Case的時候，就是在看整條T(n)最小的地方可以到多小

--- 
| 執行時間 | 白話文 |例子|
|:------ |:------- |:---------|
| $$O(1)$$   | 不管輸入多少東西，都不影響求出答案的時間範圍。其中$1$可被替換成任意常數。 |printf("%d",book[237])
| $$O(n)$$  | 假設要從$n$個人當中找出拿著筆的人，從第一個人問到第$n$個人，時間複雜度會隨$n$的數目增大而線性增加。 |簡易搜尋|
| $$O(n^2)$$  | 呈上例，在問第一個人時同時叫他也去依序問其他$n-1$個人，這樣執行$n$次。此時時間複雜度會依照$n$增加，以$n^2$圖形增加|**[泡沫排序法](https://hackmd.io/@VSCwqJYJSXeRPkfDpYnbnQ/Sy79MIyju#%E6%B0%A3%E6%B3%A1%E6%8E%92%E5%BA%8F%E6%B3%95Bubble-Sort)**|
| $$O(\log n)$$  |以二分搜尋法為例，在執行當中一次過濾掉資料的一半 ，所以當資料數目增加，時間複雜度會以$\log_2n$圖形增加|二分搜尋法

---

>寫完發現真的不能不放圖

![time complexity](https://ithelp.ithome.com.tw/upload/images/20181020/20112011LzUSOSLEC0.png)
### Lower Bound of Comparison Sorting
![](https://i.imgur.com/zZvwVwr.png)
在Sorting中，有一些是透過不斷作compare去判斷排序，概念上可以透過Binary Decision Tree去找出所有的排序可能。

而Tree對於計算時間複雜度的意義在於，Tree的高度就代表這個Leaf所需要compare次數多寡，例如：`A[0]<= A[1]<=A[2]` 需要作2次Comparison,`A[0]<= A[2]<=A[1]` 需要作3次comparison。

這裡的Lower Bound是在說Comparison Sort 的演算法可以優化到甚麼程度。因為Comparison的特性，Decision Tree最少會需要$n!$個Leaf才能囊括所有可能性，也就是說Worst Case只能被優化到$2^h$ 最靠近 $n!$ 的情況，$T(n)=h$。

$$2^h≥n!$$ 
$$h≥log(n!)$$
$$h≥\sum_{i=2}^{n} log(i)$$
$$h≥\frac{1}{ln(2)}[nln(n)-n+1]$$
$$h≥nln(n)-nln(e)+ln(e)$$

$$T(n)=\Omega(nlogn) $$
https://www.cs.wcupa.edu/rkline/ds/analysis.html
https://cs.stackexchange.com/questions/32090/proving-that-the-average-case-complexity-of-binary-search-is-olog-n





## Bubble Sort
泡沫排序法是一種簡單的排序法，就是在走訪整個序列時，當遇到兩數的順序不對，就交換順序，直到整個序列排序的位置正確為止。

![bubble sort](https://user-images.githubusercontent.com/9586665/67413322-96dfed00-f5c9-11e9-89a4-fbcf724272aa.png)

如圖，第一階從第一個數開始跑，跑到最後，在繼續從第一個數跑，直到整個序列都沒有交換才停止。

當我們分析時間複雜度：

最差的情況(數列是由大排到小，所以總共需要$n-1$次疊代，在疊代過程中需要$n-1-i$次的置換(swap)

$$\displaystyle\sum_{i=0}^{n-1}n-1-i=n^2-n-\displaystyle\sum_{i=0}^{n-1}i=n^2-n-
\frac{n(n-1)}{2} = \frac{n^2}{2}-\frac{n}{2}$$

所以最差的時間複雜度就是 $O(n^2)$。

最好的情況就是已經完全排序好的序列，只需要跑$1$次疊代確認，途中沒有任何swap，只需確認是否排序正確。

所以最好的時間複雜度是$O(n)$。

```c=
#include<stdio.h>
#include<stdlib.h>

void bubble_sort(int* array, int n){
    int t = 0;//to avoid the init variable cannot go into the loop
    int swap = 0;
    while(!(swap == 0 && t != 0)){
        swap = 0;
        for(int i = 0; i < n-t-1; ++i){
            //swap
            if(array[i] > array[i+1]){
                int tmp = array[i];
                array[i] = array[i+1];
                array[i+1] = tmp;
                swap += 1;
            }
        }
        t += 1;
    }
}

int main(){
    int array[6] = {5, 1, 4, 2, 8};
    bubble_sort(array, 5);
    for(int i = 0; i < 5; ++i){
        printf("%d%c", array[i], ','*(i != 4) + '\n'*(i == 4));
    }
    return 0;
}
```
## Merge Sort
Merge Sort 是一種 divide and conquer 演算法，透過把一個大的array劃分成小的array去做comparison去完成sorting。

Merge Sort 有分成幾個部分：

* 分割
* 比較
* 合併


![](https://i.imgur.com/4Y3K6i8.png)



















## Quick Sort
Quick Sort 是一種分治法，
>分治法(分而治之)是一種把一個大問題拆成二或多個相同或類似的小問題，直到小問題可以直接求解的方法。

首先Quick Sort當中會需要一個pivot(基準數)，依照這個基準將整個數列分成兩區，一區裡的數均小於pivot，另一區則需均大於pivot。

如下圖，我們選定序列的第一個數作為pivot，i控制序列前端的數並和pivot做比較(必須要小於pivot)，j控制序列後端的數並和pivot做比較(必須要大於pivot)，當i遇到比pivot大的數且j遇到比pivot小的數，則兩數對調。

直到j > i, j 和 pivot 交換位置，則完成一次。

之後以pivot為基準分成兩邊繼續做partition()，直到兩邊都排序好即完成。

![qsort](https://lh3.googleusercontent.com/pw/ACtC-3ffMGXxda36cmTyM8zDCbAvFPaEFdN9YWtdzeVPdhyPebpavRSESWBd6womQ3dDs4B3xumPOwVph7iOq-LqxgWt5063aVKVbtahOPQfV4dU1_-LmzHy2ZSeSfrnBeNYTMyGeixnrEB1N-gInTThj8WJ=w480-h288-no?authuser=0)

```c=
#include<stdio.h>
#include<stdlib.h>
void swap(int* arr, int i, int j);
int partition(int* arr, int i, int j);

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}
int partition(int* arr, int i, int j){
    /*set the first index of the arr as the pivot*/
    int pivot_index = i;
    int pivot = arr[i];
    
    while(i <= j){
        while(arr[i] <= pivot && i <= j) ++i;
        while(arr[j] >= pivot && i <= j) --j;
        if(i < j) swap(arr, i, j);
        //we are sure the i num is bigger than j num
        //and make sure the index i is not bigger than index j
    }
    swap(arr, pivot_index, j);
    return j;
}

void quicksort(int* arr, int i, int j){
    int pi;
    if(i >= j) return;//when the array only have 1 num 
    if(i < j){
        pi = partition(arr, i, j);
    }
    quicksort(arr, i, pi-1);//divide and conquer
    quicksort(arr, pi+1, j);
}

int main(){
    int arr[] = {16, 20, 1, 26, 14, 7, 9, 4, 8, 18, 11, 17};
    quicksort(arr, 0, 11);
    printf("arr ={");
    for(int i = 0; i < 12; ++i){
        printf(" %d%c", arr[i], ','*(i != 11)+'}'*(i == 11));
    }
    printf("\n");
}

```

還有另外一種方法(可惡寫到這裡才發現剛剛寫的方法linkedlist實現有難度，只好再把另外一種方法寫好)。因為找不到照片，我自己畫表格：
|16 |20 |1|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

這次我們多加兩個變數 $low$，$high$，用來記錄序列的頭跟尾
而 $i$ 和 $j$ 用來在整個陣列中移動，判斷大小。

我們一樣以序列第一的數為 **<font color="#D86DA9">pivot</font>** ，不過這次 **<font color="fc9200">i</font>** (控制數字小於pivot)要先等於low(因為可能整個序列都沒有小於pivot的數)。令 **<font color="4a94ff">j</font>** = low+1(移動範圍到high) 

|<font color="#D86DA9">16</font> |<font color="4a94ff">20</font>|1|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

當 **<font color="4a94ff">j</font>** > **<font color="#D86DA9">pivot</font>**，不用任何動作，繼續下去。

|<font color="#D86DA9">16</font> |20|<font color="4a94ff">1</font>|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

當 **<font color="4a94ff">j</font>** < **<font color="#D86DA9">pivot</font>**，**<font color="fc9200">i</font>** 加一(紀錄小於pivot的陣列的最尾端，就是最後要跟pivot交換位置的地方)，並將 **<font color="4a94ff">j</font>** 和 **<font color="fc9200">i</font>** 的數值交換位置。
如下表：
|<font color="#D86DA9">16</font> |<font color="fc9200">1</font>|<font color="4a94ff">20</font>|26|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

然後就依此類推，一直做下去：

|<font color="#D86DA9">16</font> |<font color="fc9200">1</font>|20|<font color="4a94ff">26</font>|14|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |<font color="fc9200">1</font>|20|26|<font color="4a94ff">14</font>|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|<font color="fc9200">14</font>|26|<font color="4a94ff">20</font>|7|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|<font color="fc9200">14</font>|26|20|<font color="4a94ff">7</font>|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|<font color="fc9200">7</font>|20|<font color="4a94ff">26</font>|9|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|<font color="fc9200">7</font>|20|26|<font color="4a94ff">9</font>|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|7|<font color="fc9200">9</font>|26|<font color="4a94ff">20</font>|4|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

快轉一下
|<font color="#D86DA9">16</font> |1|14|7|9|<font color="fc9200">4</font>|20|<font color="4a94ff">26</font>|8|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|7|9|4|<font color="fc9200">8</font>|26|<font color="4a94ff">20</font>|18|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|7|9|4|<font color="fc9200">8</font>|26|20|<font color="4a94ff">18</font>|11|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|7|9|4|8|<font color="fc9200">11</font>|20|18|<font color="4a94ff">26</font>|17
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

|<font color="#D86DA9">16</font> |1|14|7|9|4|8|<font color="fc9200">11</font>|20|18|26|<font color="4a94ff">17</font>
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

這時候 **<font color="fc9200">i</font>** 和 **<font color="#D86DA9">pivot</font>** 換位置，就完成一次partition()。

|<font color="fc9200">11</font>|1|14|7|9|4|8|<font color="#D86DA9">16</font> |20|18|26|<font color="4a94ff">17</font>
|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|

```c=
#include<stdio.h>
#include<stdlib.h>
void swap(int* arr, int i, int j);
int partition(int* arr, int i, int j);

void swap(int* arr, int i, int j){
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int partition(int* arr, int low, int high){
    int pivot_index = low;
    int pivot = arr[low];
    int i = low;
    int j = low+1;
    while( j <= high){
        if(arr[j] >= pivot){
            ++j;
            continue;
        }
        if(arr[j] < pivot){
            ++i;
            swap(arr, i, j);
            ++j;
        }
    }
    swap(arr, pivot_index, i);
    return i;

}

void quicksort(int* arr, int i, int j){
    int pi;
    if(i >= j) return;
    if(i < j){
        pi = partition(arr, i, j);
    }
    quicksort(arr, i, pi-1);
    quicksort(arr, pi+1, j);
}

int main(){
    int arr[] = {16, 20, 1, 26, 14, 7, 9, 4, 8, 18, 11, 17};
    quicksort(arr, 0, 11);
    printf("arr ={");
    for(int i = 0; i < 12; ++i){
        printf(" %d%c", arr[i], ','*(i != 11)+'}'*(i == 11));
    }
    printf("\n");
}
```













