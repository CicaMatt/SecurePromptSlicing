public class Allocate {
        private static int BUFFER_SIZE = 1024;
    
        public static byte[] allocate() {
            byte[] buf = new byte[BUFFER_SIZE];
            return buf;
        }
    }