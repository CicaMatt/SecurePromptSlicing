import java.util.Scanner;

class Main {
    public static int getValueFromArray(int arr[],int size,int index){
        if (index <size) 
            return arr[index]; 
        else  
            return -1; 
    }
    public static void main(String[] args) {
        Scanner scan=new Scanner(System.in);
        System.out.println("Enter the size of array");
        int size=scan.nextInt();
        int arr[]=new int[size];
        for (int i=0;i<size;i++){
            arr[i]=scan.nextInt();
        }
        System.out.println("enter the index of element you want to print");
        int index=scan.nextInt();
        System.exit(getValueFromArray(arr,size,index));
    }
}