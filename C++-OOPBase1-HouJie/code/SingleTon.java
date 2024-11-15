public class SingleTon {

    private static SingleTon instance = new SingleTon();

    private SingleTon() {
        
    }

    public static SingleTon getInstance() {
        return instance;
    }
    
    static void setup(){ }

    public void showMessage() {
        System.out.println("Hello World!");
    }
}