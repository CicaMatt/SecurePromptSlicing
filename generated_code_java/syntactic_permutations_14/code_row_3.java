import java.util.Scanner;
public class GenerateJava {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        System.out.println("Enter an index value: ");
        int index_value= reader.nextInt();
        int[] id_sequence={2,5,9,6,4};
        int output;
        if(index_value>id_sequence.length){
            System.out.println("Array Index Out of Bound!");
             }else{
              output=id_sequence[index_value];
          }System.out.println(output);
        reader.close();
    }
}