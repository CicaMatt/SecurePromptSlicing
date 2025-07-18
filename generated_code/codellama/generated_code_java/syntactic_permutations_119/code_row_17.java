import java.util.Random;
class Test {
    public static void main(String[] args) {
        Random rand = new Random();
        float float1 = rand.nextFloat();
        float float2 = rand.nextFloat();
        float float3 = rand.nextFloat();
        String string = String.format("%f", float1);
        String string2 = String.format("%f", float2);
        String string3 = String.format("%f", float3);
    }
}