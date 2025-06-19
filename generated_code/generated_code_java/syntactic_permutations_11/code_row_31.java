import java.util.*;
class GetValueFromArray{
    public static void main(String[] args){
        Scanner scan = new Scanner(System.in);
        int n = scan.nextInt();
        System.exit(getValueFromArray(id_sequence, id_sequence.length, n));
    }

    static int getValueFromArray(int array[], int size, int index){
        if (index >= 0 && index < size)
            return array[index];
        else
            return -1;
    }
}