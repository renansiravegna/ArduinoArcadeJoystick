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
                {"c_", VirtualKeyCode.UP},
                {"_c", VirtualKeyCode.UP},

                {"d_", VirtualKeyCode.RIGHT},
                {"_d", VirtualKeyCode.RIGHT},

                {"b_", VirtualKeyCode.DOWN},
                {"_b", VirtualKeyCode.DOWN},

                {"e_", VirtualKeyCode.LEFT},
                {"_e", VirtualKeyCode.LEFT},

                {"a_", VirtualKeyCode.VK_A},
                {"_a", VirtualKeyCode.VK_A},

                {"s_", VirtualKeyCode.VK_S},
                {"_s", VirtualKeyCode.VK_S},

                {"r_", VirtualKeyCode.VK_D},
                {"_r", VirtualKeyCode.VK_D}
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

                if (comando.Key.StartsWith("_"))
                    _inputSimulator.Keyboard.KeyUp(codigoDaTecla);
                else
                    _inputSimulator.Keyboard.KeyDown(codigoDaTecla);
            }
        }
    }
}