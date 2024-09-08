#include "disasm.h"

thread_local ppc::DisassemblerEngine ppc::gBigEndianDisassembler{ BFD_ENDIAN_BIG, "cell 64"};

ppc::DisassemblerEngine::DisassemblerEngine(bfd_endian endian, const char* options)
{
    INIT_DISASSEMBLE_INFO(info, stdout, fprintf);
    info.arch = bfd_arch_powerpc;
    info.endian = endian;
    info.disassembler_options = options;
}

int ppc::DisassemblerEngine::Disassemble(const void* code, size_t size, uint64_t base, ppc_insn& out)
{
    if (size < 4)
    {
        return 0;
    }

    info.buffer = (bfd_byte*)code;
    info.buffer_vma = base;
    info.buffer_length = size;
    return decode_insn_ppc(base, &info, &out);
}
