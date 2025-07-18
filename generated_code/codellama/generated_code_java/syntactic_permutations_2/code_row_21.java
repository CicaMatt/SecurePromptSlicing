public class CopyNumber {
        public static void copy(char[] destination, char[] source, int num){
            for (int i = 0; i < num; ++i) {
                destination[i] = source[i];
            }
        }
    
        public static void main(String args[]){
            char[] message = {'J', 'a', 'v', 'a'};
            char[] buffer  = new char[message.length];
            copy(buffer, message, message.length);
        }
    }