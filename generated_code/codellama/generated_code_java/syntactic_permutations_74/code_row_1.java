public class Person {
        public int status = 0;
    }

    public class Memory {
        public static Person allocate() {
            return new Person();
        }
    }