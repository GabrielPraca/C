using System;
using System.Collections.Generic;
using System.Text;

namespace somatorio
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Title = "somatorio";

            float soma = 0;
            float soma2 = 0;
            int i = 0;
            int QntSom = 0;
            float[] somatorio;

            Console.Write("digite a quantidade de numeros do conjunto: ");
            QntSom = Convert.ToInt32(Console.ReadLine());
            Console.Clear();

            somatorio = new float[QntSom];

            while (i < QntSom)
            {
                Console.Write("digite o valor " + Convert.ToInt32(i + 1) + ": ");
                somatorio[i] = Convert.ToInt32(Console.ReadLine());
                
                i++;
            }

            i = 0;

            while (i < QntSom)
            {
                soma = soma + somatorio[i];
                i++;
            }

            i = 0;

            while (i < QntSom)
            {
                soma2 = soma2 + (float)Math.Pow(somatorio[i],2);
                i++;
            }
            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.Write("\nO somatório do conjunto é: " + soma);
            Console.Write("\nO somatório do conjunto ao quadrado é: " + soma2);

            Console.Read();
        }
    }
}
