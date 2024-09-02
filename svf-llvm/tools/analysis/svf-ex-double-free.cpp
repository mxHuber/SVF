#include "MemoryModel/PointerAnalysis.h"
#include "SABER/DoubleFreeChecker.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "WPA/Andersen.h"
#include <fstream> // std::ofstream
#include <iostream>
#include <llvm/Support/Casting.h>

using namespace llvm;
using namespace std;
using namespace SVF;

int main(int argc, char** argv)
{
    std::vector<std::string> moduleNameVec;
    moduleNameVec =
        OptionBase::parseOptions(argc, argv, "Whole Program Points-to Analysis",
                                 "[options] <input-bitcode...>");

    SVFModule* svfModule = LLVMModuleSet::buildSVFModule(moduleNameVec);

    // LLVMContext
    // setOpaquePointers(true)

    /// Build Program Assignment Graph (SVFIR)
    SVFIRBuilder builder(svfModule);
    SVFIR* pag = builder.build();

    DoubleFreeChecker DFC = DoubleFreeChecker();
    DFC.runOnModule(pag);
#if 0
    if (DFC.getBugReport().getBugSet().empty())
    {
        std::cout << "\n" << std::endl;
        std::cout << "No bugs were found!!!" << std::endl;

        std::cout << "svfModule->getModuleIdentifier(): "
                  << svfModule->getModuleIdentifier() << std::endl;
        std::cout << "\n" << std::endl;
    }

    for (const auto* Bug : DFC.getBugReport().getBugSet())
    {
        if (const auto* DFBug = llvm::dyn_cast_or_null<DoubleFreeBug>(Bug))
        {
            std::string OutName = DFBug->getLoc();
            std::cout << "LocName:" << OutName << std::endl;
            OutName = OutName.substr(0, OutName.size() - 3);

            if (OutName.substr(OutName.size() - 3, OutName.size()) == "cpp")
            {
                OutName = OutName.substr(0, OutName.size() - 4);
            }
            else
            {
                OutName = OutName.substr(0, OutName.size() - 2);
            }

            for (int Num = 0; Num < 3; Num++)
            {
                int Counter = 0;
                for (const char CurrChar : OutName)
                {
                    Counter++;
                    if (CurrChar == ':')
                    {
                        break;
                    }
                }

                OutName = OutName.substr(Counter, OutName.size() - 1);
            }

            // cut off ' "'
            OutName = OutName.substr(2, OutName.size() - 1);

            for (int CurrWhileCount = 0; CurrWhileCount < OutName.size();
                 CurrWhileCount++)
            {
                if (OutName.at(CurrWhileCount) == '/')
                {
                    OutName =
                        OutName.substr(CurrWhileCount + 1, OutName.size());
                    CurrWhileCount = 0;
                }
            }

            OutName = OutName + "_svfout";
            OutName =
                "/home/max/Desktop/dev/Arbeit/VulnerableCommits/svf-outputs/" +
                OutName;

            std::cout << "OutName: " << OutName << std::endl;

            std::ofstream outfile(OutName, std::ofstream::out);
            // outfile.open(OutName);
            if (outfile.is_open())
            {

                outfile << DFBug->getBug();
            }
            else
            {
                std::cout << "ERROR!: Outfile wasn't open!" << std::endl;
            }
            outfile.close();
        }
    }
#endif
    // clean up memory
    AndersenWaveDiff::releaseAndersenWaveDiff();
    SVFIR::releaseSVFIR();
#if 0
    LLVMModuleSet::getLLVMModuleSet()->dumpModulesToFile(".svf.bc");
#endif
    SVF::LLVMModuleSet::releaseLLVMModuleSet();

    llvm::llvm_shutdown();
    return 0;
}
