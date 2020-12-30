import org.monostream.Tifig;

public class TifigConvert {
    public static Tifig.Options parseOptions(String[] args) {
        String inputFile = args[0];
        return new Tifig.Options(inputFile, "out.jpg", 0, 0, 90, false, false, false);
        
    }

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("missing input HEIF picture");

            return;
        }

        Tifig tifig = new Tifig();
        Tifig.Options options = parseOptions(args);

        tifig.convert(options);
    }
}
 
