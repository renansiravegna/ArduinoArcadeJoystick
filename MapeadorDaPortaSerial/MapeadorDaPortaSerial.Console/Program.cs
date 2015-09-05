using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using WindowsInput;
using WindowsInput.Native;

namespace MapeadorDaPortaSerial.Console
{
    class Program
    {
        private static Dictionary<string, VirtualKeyCode> _mapaDeComandos;
        private static SerialPort _serialPort;
        private static InputSimulator _inputSimulator;

        static void Main(string[] args)
        {
            _mapaDeComandos = new Dictionary<string, VirtualKeyCode>
            {
                {"c", VirtualKeyCode.UP},
                {"d", VirtualKeyCode.RIGHT},
                {"b", VirtualKeyCode.DOWN},
                {"e", VirtualKeyCode.LEFT},
                {"9", VirtualKeyCode.VK_A},
                {"8", VirtualKeyCode.VK_S},
                {"7", VirtualKeyCode.VK_D},
                {"6", VirtualKeyCode.VK_F},
                {"5", VirtualKeyCode.VK_Z},
                {"4", VirtualKeyCode.VK_X},
                {"3", VirtualKeyCode.VK_C},
                {"2", VirtualKeyCode.VK_V}
            };

            _serialPort = new SerialPort("COM4", 9600, Parity.None, 8, StopBits.One)
            {
                Handshake = Handshake.None,
                WriteTimeout = 500
            };

            _serialPort.DataReceived += AoReceberMensagem;
            _serialPort.Open();

            _inputSimulator = new InputSimulator();

            while (true) { }
        }

        private static void AoReceberMensagem(object sender, SerialDataReceivedEventArgs e)
		{
		    var mensagemDaPorta = _serialPort.ReadLine();
            var comandosRecebidos = _mapaDeComandos.Where(comando => mensagemDaPorta.Contains(comando.Key)).ToList();
            
            foreach (var comando in comandosRecebidos)
            {
                System.Console.WriteLine(comando);
                var codigoDaTecla = _mapaDeComandos[comando.Key];

                if (comando.Key.StartsWith("-"))
                    _inputSimulator.Keyboard.KeyUp(codigoDaTecla);
                else
                    _inputSimulator.Keyboard.KeyDown(codigoDaTecla);
            }
        }
    }
}