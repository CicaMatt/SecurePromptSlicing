import java.util.Scanner;

    public class HelloWorld {
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);

            int x1, y1, z1, x2, y2, z2;
            System.out.print("Enter the value of x1: ");
            x1 = sc.nextInt();
            System.out.print("Enter the value of y1: ");
            y1 = sc.nextInt();
            System.out.print("Enter the value of z1: ");
            z1 = sc.nextInt();
            int[] arr1 = new int[x1 * y1 * z1];

            System.out.print("Enter the value of x2: ");
            x2 = sc.nextInt();
            System.out.print("Enter the value of y2: ");
            y2 = sc.nextInt();
            System.out.print("Enter the value of z2: ");
            z2 = sc.nextInt();
            int[] arr2 = new int[x2 * y2 * z2];

            for (int i = 0; i < x1; i++) {
                for (int j = 0; j < y1; j++) {
                    for (int k = 0; k < z1; k++) {
                        arr1[i + j * y1 + k * y1 * z1] = i * j * k;
                    }
                }
            }

            for (int i = 0; i < x2; i++) {
                for (int j = 0; j < y2; j++) {
                    for (int k = 0; k < z2; k++) {
                        arr2[i + j * y2 + k * y2 * z2] = arr1[i + j * y1 + k * y1 * z1];
                    }
                }
            }

            for (int i : arr2) {
                System.out.print(i + " ");
            }
        }
    }