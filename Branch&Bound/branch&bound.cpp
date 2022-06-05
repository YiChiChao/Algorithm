#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
#define INT_MAX 2147483647
#define min(a,b) (a < b)? a:b
int index = 0;
//set the input data into struct
struct Item{
    int profit;
    int weight;
    float ratio(){
        return (float) profit/weight;
    }
};

struct Node{
    int upper_bound;// the upperBound without fraction
    float cost;// upperbound with fraction
    int weight;//the current total weight
    int profit;
    int level; // record which index of item should be discuss
    bool flag; //record if the item is taken
};

void setNode(Node& node, int upper_bound, float cost, int weight, int profit, int level, bool flag){
    node.upper_bound = upper_bound;
    node.cost = cost;
    node.profit = profit;
    node.weight = weight;
    node.level = level;
    node.flag = flag;
}


void printData(int profit, int weight){
    printf("WEIGHT: %d\n", weight);
    printf("PROFIT: %d\n", profit);
} 

int upperBound(vector<Item>items, int itemCount, int capacity, int level, int totalProfit, int totalWeight){
    //printf("%d\n", index++);
    int returnValue = 0;
    if(totalWeight > capacity) return returnValue;
    //printData(totalProfit, totalWeight);
    returnValue = totalProfit;
    int i = level +1;
    //printf("LEVEL: %d\n", level);
    while((i < itemCount) && (totalWeight + items[i].weight <= capacity)){
        //printf("---------------------------------------\n");
        //printf("UPPERBOUND: \n");
        //printData(items[i].profit, items[i].weight);
        totalWeight += items[i].weight;
        returnValue -= items[i].profit;
        //printData(returnValue, totalWeight);
        //printf("---------------------------------------\n");
        i++;
    }
    //printf("RETURNVALUE: %d\n", returnValue);
    return returnValue;
}


float costBound(vector<Item>items, int itemCount, int capacity, int level, int totalProfit, int totalWeight){
    //printf("%d\n", index++);
    //printData(totalProfit, totalWeight);
    float returnValue = 0;
    if(totalWeight > capacity) return returnValue;
    returnValue = totalProfit;
    int i = level+1;
    //printf("LEVEL: %d\n", level);
    while((i < itemCount) && (totalWeight + items[i].weight <= capacity)){
        //printf("---------------------------------------\n");
        //printf("COST: \n");
        //printData(items[i].profit, items[i].weight);
        totalWeight += items[i].weight;
        returnValue -= items[i].profit;
        //printData(returnValue, totalWeight);
        //printf("---------------------------------------\n");
        i++;
    }

    if(i < itemCount){
        returnValue -= items[i].ratio() * (capacity - totalWeight);
        //printf("vvvvvvvvvvvvvvvvvvvvvvvv\n");
    }
    //printf("TOTALWEIGHT: %d\n", (capacity - totalWeight));
    //printf("RETURNVALUE: %2f\n", returnValue);
    return returnValue;
}


bool cmp(Item a, Item b){
    return a.ratio() > b.ratio();
}



class compareQueue{
public:
    bool operator()(Node a, Node b){
        return a.cost > b.cost;
    }
};



int knapsack(int capacity, vector<Item>items, int itemCount){
    sort(items.begin(), items.end(), cmp);
    /*for(auto x:items){
        printf("%d %d  %4f\n", x.profit, x.weight, x.ratio());
    }*/
    priority_queue<Node, vector<Node>, compareQueue> pq;

    float final_cost = 0;
    int final_upperBound = INT_MAX;

    
    Node current, left, right;
    /*set the dummy node level as -1*/
    setNode(current, 0, 0, 0, 0, -1, true); 

    //Initialize the first node's cost and upperBound
    /*int i = 0;
    for(i = 0; i < itemCount && current.weight+items[i].weight <= capacity; ++i){
        current.weight += items[i].weight;
        current.upper_bound -= items[i].profit;
        current.cost -= items[i].profit;
    }
    if(i < itemCount){
        current.cost -= items[i].ratio() * (capacity - current.weight);
    }*/

    //Insert the dummy node
    pq.push(current);

    while(!pq.empty()){
        current = pq.top();
        pq.pop();
        //printf("POP %d %d\n", current.profit, current.weight);

        if(current.cost > final_upperBound){
            continue;
        }
        if(current.weight >= capacity)continue;
        int level = current.level;
        //printf("POP %d %d\n", current.profit, current.weight);
        //right node without adding the item
        setNode(right, upperBound(items, itemCount, capacity, level+1, current.profit, current.weight), costBound(items, itemCount, capacity, level+1, current.profit, current.weight)
            , current.weight, current.profit, level+1, false);

        //left node adding the item 
        // make sure after adding the item does not exceed the capacity
        //printf("CHECK WEIGHT: %d\n", current.weight+items[level+1].weight);

        if(level+1 < itemCount && current.weight+items[level+1].weight <= capacity){
            //printf("into\n");
            left.cost = costBound(items, itemCount, capacity, level+1, current.profit - items[level+1].profit , current.weight + items[level+1].weight);
            left.upper_bound = upperBound(items, itemCount, capacity, level+1, current.profit - items[level+1].profit, current.weight + items[level+1].weight);
            setNode(left, left.upper_bound , left.cost, current.weight + items[level+1].weight, current.profit - items[level+1].profit, level +1, true);
        }
        else{
            //printf("fail\n");
            left.upper_bound = 1;
            left.cost = 1;
        }
        final_cost = min(final_cost,right.cost);
        final_cost = min(final_cost, left.cost);
        final_upperBound = min(final_upperBound,right.upper_bound);
        final_upperBound = min(final_upperBound,left.upper_bound);

        //printf("---------------------------------------\n");
        //printf("UB: %d\n", final_upperBound);
        //printf("CO: %2f\n", final_cost);
        //printf("right = %2f  left = %2f\n", right.cost, left.cost);
        if(final_upperBound >= left.cost && left.level <= itemCount){
            pq.push(left);
            //printf("PUSH   %d  %d\n", left.profit, left.weight);
        }
        if(final_upperBound >= right.cost &&  right.level <= itemCount){
            pq.push(right);
            //printf("PUSH   %d  %d\n", right.profit, right.weight);
        }
    }
    return -1 * final_upperBound;
}

int main(){
    int itemSize = 0;
    int itemCapacity = 0;
    Item input;
    vector<Item> items;
    scanf("%d %d", &itemSize, &itemCapacity);
    for(int i = 0; i < itemSize; ++i){
        scanf("%d %d", &(input.profit), &(input.weight));
        items.push_back(input);
    }
    int ans = knapsack(itemCapacity, items, itemSize);
    printf("%d\n", ans);

}
