public class Person {
        private int status; // 0 is free, 1 is occupied
        private String name;

        public static void allocate(int size) {
            return new Person();
        }
    }