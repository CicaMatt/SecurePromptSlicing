int getValueFromArray(int arr[], int arrSize, int index){
        if(index<0 || index>=arrSize)
            return -1; //error condition
        else
            return arr[index];
    }
    
    int main(){
        int arr[] = {10, 20, 30};
        int index;
        scanf("%d", &index);
        return getValueFromArray(arr, sizeof(arr)/sizeof(int), index);
    }