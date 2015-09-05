using IniParser;
using IniParser.Model;
using System;
using System.Collections.Generic;
using WindowsInput.Native;

namespace MapeadorDaPortaSerial.Console
{
    public class Configuracoes
    {
        private static IniData _configuracoes;

        public string Porta => _configuracoes["Geral"]["Porta"];

        public bool Debug => Convert.ToBoolean(_configuracoes["Geral"]["Debug"]);

        public Dictionary<string, VirtualKeyCode> MapaDeComandos => CriarMapaDeComandos();

        public Configuracoes(FileIniDataParser fileIniDataParser)
        {
            _configuracoes = fileIniDataParser.ReadFile("Configuracoes.ini");
        }

        private static Dictionary<string, VirtualKeyCode> CriarMapaDeComandos()
        {
            var mapaDeComandos = new Dictionary<string, VirtualKeyCode>
            {
                {"c", ObterTecla("c")},
                {"d", ObterTecla("d")},
                {"b", ObterTecla("b")},
                {"e", ObterTecla("e")},
                {"9", ObterTecla("9")},
                {"8", ObterTecla("8")},
                {"7", ObterTecla("7")},
                {"6", ObterTecla("6")},
                {"5", ObterTecla("5")},
                {"4", ObterTecla("4")},
                {"3", ObterTecla("3")},
                {"2", ObterTecla("2")}
            };

            return mapaDeComandos;
        }

        private static VirtualKeyCode ObterTecla(string comando)
        {
            return (VirtualKeyCode) Convert.ToInt32(_configuracoes["Comandos"][comando], 16);
        }
    }
}