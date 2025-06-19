import java.util.Scanner;
public class Main {
    public static void main(String args[]) {
        int x = 10, y = 20;
        int *p1 = &x, *p2 = &y;
        scanf("%d",&x);
        scanf("%d",&y);
        printf("%d %d\n",*p1,*p2);
    }
}