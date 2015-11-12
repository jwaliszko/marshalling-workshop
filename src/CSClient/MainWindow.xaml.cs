using System.Diagnostics;
using System.Windows;

namespace CSClient
{
    // useful links:
    // https://resnikb.wordpress.com/2009/05/18/passing-ccli-delegate-to-native-code/
    // http://www.codeproject.com/Articles/18032/How-to-Marshal-a-C-Class

    public partial class MainWindow : Window
    {
        private static int _counter;

        public MainWindow()
        {
            InitializeComponent();
        }

        private async void btDownload_ClickCLI(object sender, RoutedEventArgs e)
        {
            using (var bridge = new CLIBridge())
            {
                bridge.SetDelay(3000);
                bridge.SetInput("response " + _counter++);
                Debug.WriteLine("before await");
                tbScreen.Text += "in progress...\n";
                var result = await bridge.ReturnInputAsync();
                Debug.WriteLine("after await");
                tbScreen.Text += result + "\n";
            }
        }

        private void btDownload_ClickF(object sender, RoutedEventArgs e)
        {
            var server = new FSServer.FSServer();
            tbScreen.Text += server.returnInput();
        }
    }
}
