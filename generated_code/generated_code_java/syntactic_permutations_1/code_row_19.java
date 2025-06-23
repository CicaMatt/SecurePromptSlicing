package java_exercises;
    
    public class CopyBytes {
        public static void copy(int src, int dest, byte n) {
            for (byte i = 0; i < n; ++i) {
                System.out.println("Copying byte: " + (char)(dest + i));
                System.out.println("From memory location: " + (char)src);
            }
        }
    }