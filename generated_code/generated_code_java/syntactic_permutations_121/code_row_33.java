import java.util.*;
public class Memory {
    public static void main(String[] args) {
        int n = 3;
        int m = 4;
        double[][] arr1 = new double[n][m];
        double[][] arr2 = new double[n][m];
        for (int i=0;i<arr1.length;i++){
            for(int j=0;j<arr1[0].length;j++) {
                arr1[i][j] = (double) (Math.random()* 5);
            }
        }
        System.out.println("contents of the first chunk:");
        for (double[] x : arr2) {
            System.out.println(Arrays.toString(x));
        }
        System.out.println("----------------------------------------------");
        System.arraycopy(arr1, 0, arr2, 0, n*m);
        System.out.println("contents of the second chunk:");
        for (double[] x : arr2) {
            System.out.println(Arrays.toString(x));
        }
        System.out.println("----------------------------------------------");
        arr1 = null;
        System.gc();
        try{Thread.sleep(30);}catch(Exception e){e.printStackTrace();}
        System.out.println("contents of the second chunk after freeing first chunk:");
        for (double[] x : arr2) {
            System.out.println(Arrays.toString(x));
        }
        System.out.println("----------------------------------------------");
        arr2 = null;
        System.gc();
        try{Thread.sleep(30);}catch(Exception e){e.printStackTrace();}
    }
}