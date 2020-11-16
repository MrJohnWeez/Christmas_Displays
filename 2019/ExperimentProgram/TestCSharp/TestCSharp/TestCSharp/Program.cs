using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            string userNeededValues = "";
            string userLowRange = "";
            string userHighRange = "";
            string userCountBy = "";

            Console.WriteLine("Input number of needed values:");
            userNeededValues = Console.ReadLine();
            Console.WriteLine("Input starting range:");
            userLowRange = Console.ReadLine();
            Console.WriteLine("Input ending range:");
            userHighRange = Console.ReadLine();
            Console.WriteLine("Input count by value:");
            userCountBy = Console.ReadLine();

            int neededValues = Convert.ToInt32(userNeededValues);
            int lowRange = Convert.ToInt32(userLowRange);
            int highRange = Convert.ToInt32(userHighRange);
            int countBy = Convert.ToInt32(userCountBy);
            

            List<int> values = new List<int>();
            for(int i = lowRange; i <= highRange; i += countBy)
            {
                values.Add(i);
            }
            float indexer = 0;
            int totalValues = values.Count;
            float addIndex = 1;
            if(totalValues > neededValues)
            {
                addIndex = (float)totalValues / (float)neededValues;
            }

            float interval = (float)neededValues / (float)totalValues;
            float currentInterval = interval;

            Console.WriteLine("\n\nGenerating file...");
            for (int i = 0; i < neededValues-1; i++)
            {
                
                if((int)indexer <= totalValues)
                {
                    Console.WriteLine(values[(int)indexer]);
                }
                else
                {
                    Console.WriteLine(values[totalValues]);
                }
                if (i >= (int)currentInterval)
                {
                    currentInterval += interval;
                    indexer += addIndex;
                }
            }

            Console.ReadKey();
        }
    }
}
