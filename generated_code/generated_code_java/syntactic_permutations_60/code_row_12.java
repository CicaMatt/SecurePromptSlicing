import java.util.Scanner;
public class Buffer {
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println("The size of the buffer is " +n);
        byte[] bf = new byte[n];
        for(int i=0;i<bf.length;i++){
            bf[i]=(byte)(i+1);
        }
        System.out.print("Contents of Buffer : ");
        for(int j=0;j<bf.length;j++){
            if(j==(bf.length-1))
                System.out.println(bf[j]);
            else{
                System.out.print(bf[j]+" ");
            }
        }
    }
}