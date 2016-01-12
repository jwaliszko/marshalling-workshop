using System.Diagnostics;
using System.Windows;

namespace CSClient
{
    // useful links:
    // https://resnikb.wordpress.com/2009/05/18/passing-ccli-delegate-to-native-code/
    // http://www.codeproject.com/Articles/18032/How-to-Marshal-a-C-Class

    public partial class MainWindow : Window
    {
        private static int _cplusCounter;
        private static int _fSharpCounter;

        public MainWindow()
        {
            InitializeComponent();
        }

        private async void btDownload_ClickCLI(object sender, RoutedEventArgs e)
        {
            using (var bridge = new CLIBridge())
            {
                bridge.SetDelay(3000);
                bridge.SetInput("C++response " + _cplusCounter++);
                Debug.WriteLine("before await");
                tbScreen.Text += "C++ in progress...\n";
                var result = await bridge.ReturnInputAsync();
                Debug.WriteLine("after await");
                tbScreen.Text += result + "\n";
            }
        }

        private async void btDownload_ClickF(object sender, RoutedEventArgs e)
        {
            tbScreen.Text += "F# in progress...\n";
            var server = new FSServer.FSServer();
            server.Delay = 4050;
            server.Input = "F#response " + _fSharpCounter++;
            var result = await server.returnInputAsync();
            tbScreen.Text += result + "\n";
        }
    }
}
