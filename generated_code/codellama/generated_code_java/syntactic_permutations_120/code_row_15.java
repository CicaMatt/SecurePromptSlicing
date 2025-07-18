import java.util.*;
class Code{
    public static void main(String []args){
        int [] a = {1,2,3};
        int [] b = new int[a.length];
        System.arraycopy(a,0,b,0,a.length);
        for (int i=0;i<b.length;i++){
            System.out.println(b[i]);
        }
    }
}