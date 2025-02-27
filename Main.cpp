#include <iostream>
#include <stdint.h>
#include <random>
#include <cmath>
#include <functional>
#include <cstdint>
#include <random>
#include <chrono>
#include <iomanip>
#include <string_view>
#include <type_traits>

#include <thread>
#include <vector>
#include <algorithm>
#include <numeric>
#include <tuple>

#ifdef _WIN32
#include <limits.h>
#include <intrin.h>
#else
#pragma clang diagnostic ignored "-Wignored-attributes"
#endif

class CPUID {
	uint32_t regs[4];

public:
	explicit CPUID(unsigned i) {
#ifdef _WIN32
		__cpuid((int*)regs, (int)i);
#elif defined(__x86_64__) || defined(__i386__)
		asm volatile
			("cpuid" : "=a" (regs[0]), "=b" (regs[1]), "=c" (regs[2]), "=d" (regs[3])
				: "a" (i), "c" (0));
		// ECX is set to zero for CPUID function 4
#else
		char* vals = (char*)regs;
		*vals++ = 'C'; *vals++ = 'P'; *vals++ = 'U'; *vals++ = ':'; *vals++ = ' ';
		*vals++ = 'U'; *vals++ = 'n'; *vals++ = 'k'; *vals++ = 'o'; *vals++ = 'w'; *vals++ = 'n'; *vals++ = ' ';
		*vals++ = 'A'; *vals++ = 'R'; *vals++ = 'M'; //Just unknown really
		*vals++ = '\0';
#endif
	}
	const uint32_t& EAX() const { return regs[0]; }
	const uint32_t& EBX() const { return regs[1]; }
	const uint32_t& ECX() const { return regs[2]; }
	const uint32_t& EDX() const { return regs[3]; }
};

static void PrintBrand() {
#if defined(__linux__) && (!defined(__x86_64__) && !defined(__i386__))
	//Non x86/x64 Linux system
	system("cat /proc/cpuinfo | grep model | grep name");
#else
	uint32_t brand[12]{};
	for (int i = 0; i < 3; i++) 
	{
		CPUID d(0x80000002 + i);
		brand[4*i + 0] = d.EAX();
		brand[4*i + 1] = d.EBX();
		brand[4*i + 2] = d.ECX();
		brand[4*i + 3] = d.EDX();
	}
	printf("%s\n", (char*)brand);
#endif
}



#define Kogge_	 (1)
#define Bob_	 (1)
#define BobAdvanced_ (1)
#define Plain_	 (1)
#define Fancy_	 (1)
#define Pext_	 (1)
#define SplitPext_	 (1)
#define Kindergarten_ (1)
#define PreSchool_ (1)
#define PextEmu_ (1)
#define Hyper_	 (1)
#define Explode_ (1)
#define HypQsc_  (1)
#define HypQscNT_ (1)
#define Rotate_	 (1)
#define Arithm_	 (1)
#define Obstrd_	 (1)
#define ObstrdNT_ (1)
#define QBB_	 (1)
#define GeneticQBB_	 (1)
#define HVar_	 (1)
#define CMagic_	 (1)
#define SMagic_  (1)
#define SMagic2_ (1)
#define Sissy_	 (1)
#define KGSSB_	 (1)
#define Dumb7_	 (1)
#define AVXShift_	 (1)
#define Leorik_	 (1)
#define LeorikNT_ (1)
#define SBAMG_ (1)
#define SBAMGNT_ (1)
#define BinaryNetwork_ (1)
#define RotateBits_ (1)
#define Genetic8Ray_ (1)
#define GeneticObstruction_ (1)
#define GeneticObstructionV2_ (1)
#define FoldingHash_ (1)
#define GaloisField_ (1)
#define Gigantua_ (0)

#define MaskOf(X) _blsi_u64(X)
#define SquareOf(X) _tzcnt_u64(X)
#define Bitloop(X) for(;X; X = _blsr_u64(X))

#define Dummy(X) struct X {static inline constexpr std::string_view name = "dummy"; static void Prepare(uint64_t occ) {}static uint64_t Queen(int sq, uint64_t occ) { return 0; }};

static uint32_t rx = 123456789, ry = 362436069, rz = 521288629;
uint32_t rand32(void) { //2^96-1
	uint32_t t;
	rx ^= rx << 16; rx ^= rx >> 5; rx ^= rx << 1;
	t = rx; rx = ry; ry = rz; rz = t ^ rx ^ ry;
	return rz;
}
uint32_t rand32_state(uint32_t& x, uint32_t& y, uint32_t& z) { //2^96-1
	uint32_t t;
	x^= x<< 16; x^= x>> 5; x^= x<< 1;
	t = x; x= y; y = z; z = t ^ x^ y;
	return z;
}

uint64_t rand64() {
	return ((uint64_t)rand32() << 32ull) | rand32();
}

uint64_t rand64_state(uint32_t& x, uint32_t& y, uint32_t& z) {
	return (static_cast<uint64_t>(rand32_state(x,y,z)) << 32ull) | static_cast<uint64_t>(rand32_state(x,y,z));
}

#define Loop64(x, y) { \
{constexpr int x = 0; {y;} } \
{constexpr int x = 1; {y;} } \
{constexpr int x = 2; {y;} } \
{constexpr int x = 3; {y;} } \
{constexpr int x = 4; {y;} } \
{constexpr int x = 5; {y;} } \
{constexpr int x = 6; {y;} } \
{constexpr int x = 7; {y;} } \
{constexpr int x = 8; {y;} } \
{constexpr int x = 9; {y;} } \
{constexpr int x = 10; {y;} } \
{constexpr int x = 11; {y;} } \
{constexpr int x = 12; {y;} } \
{constexpr int x = 13; {y;} } \
{constexpr int x = 14; {y;} } \
{constexpr int x = 15; {y;} } \
{constexpr int x = 16; {y;} } \
{constexpr int x = 17; {y;} } \
{constexpr int x = 18; {y;} } \
{constexpr int x = 19; {y;} } \
{constexpr int x = 20; {y;} } \
{constexpr int x = 21; {y;} } \
{constexpr int x = 22; {y;} } \
{constexpr int x = 23; {y;} } \
{constexpr int x = 24; {y;} } \
{constexpr int x = 25; {y;} } \
{constexpr int x = 26; {y;} } \
{constexpr int x = 27; {y;} } \
{constexpr int x = 28; {y;} } \
{constexpr int x = 29; {y;} } \
{constexpr int x = 30; {y;} } \
{constexpr int x = 31; {y;} } \
{constexpr int x = 32; {y;} } \
{constexpr int x = 33; {y;} } \
{constexpr int x = 34; {y;} } \
{constexpr int x = 35; {y;} } \
{constexpr int x = 36; {y;} } \
{constexpr int x = 37; {y;} } \
{constexpr int x = 38; {y;} } \
{constexpr int x = 39; {y;} } \
{constexpr int x = 40; {y;} } \
{constexpr int x = 41; {y;} } \
{constexpr int x = 42; {y;} } \
{constexpr int x = 43; {y;} } \
{constexpr int x = 44; {y;} } \
{constexpr int x = 45; {y;} } \
{constexpr int x = 46; {y;} } \
{constexpr int x = 47; {y;} } \
{constexpr int x = 48; {y;} } \
{constexpr int x = 49; {y;} } \
{constexpr int x = 50; {y;} } \
{constexpr int x = 51; {y;} } \
{constexpr int x = 52; {y;} } \
{constexpr int x = 53; {y;} } \
{constexpr int x = 54; {y;} } \
{constexpr int x = 55; {y;} } \
{constexpr int x = 56; {y;} } \
{constexpr int x = 57; {y;} } \
{constexpr int x = 58; {y;} } \
{constexpr int x = 59; {y;} } \
{constexpr int x = 60; {y;} } \
{constexpr int x = 61; {y;} } \
{constexpr int x = 62; {y;} } \
{constexpr int x = 63; {y;} } \
}


template<int N>
static void ConstPrint(const char* name, uint64_t source[N])
{
	std::stringstream ss;
	ss << std::dec;
	ss << "static constexpr uint64_t " << name << "[" << N << "] = { ";
	ss << std::hex;
	for (int i = 0; i < N; i++) {
		ss << "0x" << source[i] << "ull";
		if (i != N - 1) ss << ", ";
	}
	ss << "};\n";
	ss << std::dec;
	std::cout << ss.str();
}


static std::string _map(uint64_t value)
{
	static std::string str(64 + 8, 'o');
	for (uint64_t i = 0, c = 0; i < 64; i++)
	{
		uint64_t bitmask = (1ull) << i;

		if ((bitmask & value) != 0) str[c++] = 'X';
		else str[c++] = '.';

		if ((i + 1) % 8 == 0) str[c++] = '\n';
	}
	return str;
}


//Reference
#include "Switch.hpp"
struct Switch_t {
	static constexpr bool Supports_Template = true;

	static inline constexpr std::string_view name = "Reference (Switch Lookup)";
	static inline constexpr std::string_view sp_op = "none";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=78235&p=907362&hilit=espresso#p907362";

	static void Prepare(uint64_t occ) {}
	static constexpr uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Switch::Queen(sq, occ); }
	template <int sq> static constexpr uint64_t Queen(uint64_t occ) { return Chess_Lookup::Lookup_Switch::Queen<sq>(occ); }
	static constexpr uint64_t Rook_Xray(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Switch::Rook_Xray(sq, occ); }
	static constexpr uint64_t Bish_Xray(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Switch::Bishop_Xray(sq, occ); }
	static constexpr uint64_t Size() { return Chess_Lookup::Lookup_Switch::Size; }
};

#if GeneticObstruction_
#include "GeneticObstructionDiff.hpp"
struct GeneticObstructionDiff_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Genetic Obstruction Difference";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr and Michael Hoffmann";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79701";
	static inline constexpr std::string_view sp_op = "countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::GeneticObstructionDiff::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::GeneticObstructionDiff::Size; }
};
#else 
Dummy(GeneticObstructionDiff_t);
#endif

#if GeneticObstructionV2_
#include "GeneticObstructionDiffV2.hpp"
struct GeneticObstructionDiffV2_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Genetic Obstruction Difference V2";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79701";
	static inline constexpr std::string_view sp_op = "countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::GeneticObstructionDiffV2::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::GeneticObstructionDiffV2::Size; }
};
#else 
Dummy(GeneticObstructionDiffV2_t);
#endif


#if FoldingHash_
#include "FoldingHash.hpp"
struct FoldingHash_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "FoldingHash - 4x fancy magic";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "tbd";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::FoldingHash::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::FoldingHash::Size; }
};
#else 
Dummy(FoldingHash_t);
#endif

#if GaloisField_
#include "GaloisField.hpp"
struct GaloisField_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "GaloisField - AVX512";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=81335";
	static inline constexpr std::string_view sp_op = "AVX512F_GFNI";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::GaloisField::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::GaloisField::Size; }
};
#else 
Dummy(GaloisField_t);
#endif


#if Gigantua_
#include "Gigantua.hpp"
struct Gigantua_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Gigantua Rotation Algorithm";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=81707&sid=ec3532ea1ce1e8014d2b579b29fddd34";
	static inline constexpr std::string_view sp_op = "AVX2 or AVX512 + GFNI";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Gigantua::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Gigantua::Size; }
};
#else 
Dummy(Gigantua_t);
#endif


#if Genetic8Ray_
#include "Genetic8Ray.hpp"
struct Genetic8Ray_t {
	static constexpr bool Supports_Template = false;

	static inline constexpr std::string_view name = "Genetic 8 Ray";
	static inline constexpr std::string_view sp_op = "bswap";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "Abstract C++ Syntax Tree Sifter (c) Daniel Infuehr";

	static inline uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Genetic8Ray::Queen(sq, occ); }
	static inline uint64_t Size() { return Chess_Lookup::Genetic8Ray::Size; }
};
#else 
Dummy(Genetic8Ray_t);
#endif


#if AVXShift_
#include "AVXShift.hpp"
struct Loop_t {
	static constexpr bool Supports_Template = false;

	static inline constexpr std::string_view name = "AVX Branchless Shift";
	static inline constexpr std::string_view sp_op = "AVX2";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79005&start=60";

	static inline uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::AVXShift::Queen(sq, occ); }
	static inline uint64_t Size() { return Chess_Lookup::AVXShift::Size; }
};
#else 
Dummy(Loop_t);
#endif

#if Dumb7_
#include "Dumb7Fill.hpp"
struct Dumb7_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Dumb7 Fill";
	static inline constexpr std::string_view author = "Gunnar Andersson";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Dumb7Fill";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Dumb7Fill::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Dumb7Fill::Size; }
};
#else 
Dummy(Dumb7_t);
#endif


#if Kogge_
#include "KoggeStone.hpp"
struct Kogge_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Kogge-Stone";
	static inline constexpr std::string_view author = "Peter M. Kogge, Harold S. Stone";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Kogge-Stone_Algorithm";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::KoggeStone::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::KoggeStone::Size; }
};
#else 
	Dummy(Kogge_t);
#endif

#if Bob_
#include "Boblookup.hpp"
struct Bob_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "Classical Bob-Mike";
	static inline constexpr std::string_view author = "Robert Hyatt and Michael Sherwin";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Classical_Approach";
	static inline constexpr std::string_view sp_op = "countr_zero, countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::BobLU::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::BobLU::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::BobLU::Size; }
};
#else 
	Dummy(Bob_t);
#endif

#if BobAdvanced_
#include "Boblookup_advanced.hpp"
	struct BobAdvanced_t {
		static constexpr bool Supports_Template = false;
		static inline constexpr std::string_view name = "Advanced Bob-Mike";
		static inline constexpr std::string_view author = "Michael Sherwin and Daniel Inf\x81hr";
		static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79078&start=50#p924653";
		static inline constexpr std::string_view sp_op = "countr_zero, countl_zero";

		static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::BobAdvanced::Queen(sq, occ); }
		static uint64_t Size() { return Chess_Lookup::BobAdvanced::Size; }
	};
#else 
	Dummy(BobAdvanced_t);
#endif

#if Leorik_
#include "Leorik.hpp"
	struct Leorik_t {
		static constexpr bool Supports_Template = false;
		static inline constexpr std::string_view name = "Leorik";
		static inline constexpr std::string_view author = "Thomas Jahn (lithander)";
		static inline constexpr std::string_view reference = "https://github.com/lithander/MinimalChessEngine";
		static inline constexpr std::string_view sp_op = "countl_zero";
	
		static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Leorik::Queen(sq, occ); }
		static uint64_t Size() { return Chess_Lookup::Leorik::Size; }
	};
#else 
	Dummy(Leorik_t);
#endif

#if LeorikNT_
#include "Leorik_IL.hpp"
	struct LeorikNT_t {
		static constexpr bool Supports_Template = false;
		static inline constexpr std::string_view name = "Leorik Inline";
		static inline constexpr std::string_view author = "Thomas Jahn (lithander)";
		static inline constexpr std::string_view reference = "https://github.com/lithander/MinimalChessEngine";
		static inline constexpr std::string_view sp_op = "countl_zero";

		static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::LeorikIL::Queen(sq, occ); }
		static uint64_t Size() { return Chess_Lookup::LeorikIL::Size; }
	};
#else 
	Dummy(LeorikNT_t);
#endif

#if Hyper_
#include "Hyperchess.hpp"
struct Hyper_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "HyperCube";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79004&p=916723&hilit=hypercube#p916723";
	static inline constexpr std::string_view sp_op = "none";

	static inline void Prepare(uint64_t occ) { Chess_Lookup::Lookup_Hyper::Prepare(occ); }
	static constexpr void Move(int from, int to) { Chess_Lookup::Lookup_Hyper::Move(from, to); }
	static constexpr void Move_Take(int from, int to) { Chess_Lookup::Lookup_Hyper::Move_Take(from, to); }
	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Hyper::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::Lookup_Hyper::Queen<sq>(occ); }
	static uint64_t Rook_Xray(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Hyper::Rook_Xray(sq); }
	static uint64_t Bish_Xray(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Hyper::Bishop_Xray(sq); }
	static uint64_t Size() { return Chess_Lookup::Lookup_Hyper::Size; }
};
#else 
	Dummy(Hyper_t);
#endif

#if Pext_
#include "Pext.hpp"
	struct Pext_t {
		static constexpr bool Supports_Template = true;
		static inline constexpr std::string_view name = "Pext constexpr";
		static inline constexpr std::string_view author = "Zach Wegner";
		static inline constexpr std::string_view reference = "https://www.chessprogramming.org/BMI2#PEXTBitboards";
		static inline constexpr std::string_view sp_op = "pext_u64";

		static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Pext::Queen(sq, occ); }
		template <int sq> static constexpr uint64_t Queen(uint64_t occ) { return Chess_Lookup::Lookup_Pext::Queen<sq>(occ); }
		static uint64_t Size() { return Chess_Lookup::Lookup_Pext::Size; }
	};
#else 
	Dummy(Pext_t);
#endif

#if SplitPext_
#include "SplitPext.hpp"
	struct SplitPext_t {
		static constexpr bool Supports_Template = false;
		static inline constexpr std::string_view name = "Split Pext";
		static inline constexpr std::string_view author = "Group Idea";
		static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=79049&start=340";
		static inline constexpr std::string_view sp_op = "pext_u64";

		static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SplitPext::Queen(sq, occ); }
		static uint64_t Size() { return Chess_Lookup::SplitPext::Size; }
	};
#else 
	Dummy(SplitPext_t);
#endif

#if PextEmu_
#include "Pext.hpp"
struct PextEmu_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Pext Emulated";
	static inline constexpr std::string_view author = "Zach Wegner"; //Daniel Inführ
	static inline constexpr std::string_view reference = "https://randombit.net/bitbashing/posts/haswell_bit_permutations.html";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Lookup_Pext::Queen_Emulated(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Lookup_Pext::Size; }
};
#else 
	Dummy(Pext_t);
#endif

#if Plain_
#include "Hash_Plain.hpp"
struct Plain_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Plain Magic BB";
	static inline constexpr std::string_view author = "Lasse Hansen";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Magic_Bitboards#Plain";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Plain::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Plain::Size; }
};
#else 
Dummy(Plain_t);
#endif

#if HVar_
#include "Hash_Var.hpp"
struct HVar_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "Fancy Magic BB - Variable shift";
	static inline constexpr std::string_view author = "Pradu Kannan";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Magic_Bitboards#Fancy";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Var::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::Var::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::Var::Size; }
};
#else 
Dummy(HVar_t);
#endif

#if CMagic_
#include "Correlationmagic.hpp"
struct CMagic_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Correlation Magic";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=82224#p949688";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Correlationmagic::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Correlationmagic::Size; }
};
#else 
Dummy(CMagic_t);
#endif

#if SMagic_
#include "Correlationmagic.hpp"
struct SMagic_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Spectral Magic";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=82224#p949688";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Correlationmagic::SpectralQueen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Correlationmagic::Size; }
};
#else 
Dummy(SMagic_t);
#endif

#if SMagic2_
#include "Spectralmagic.hpp"
struct SMagic2_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Spectral Magic Switched";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=79005&start=160";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SpectralMagic::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::SpectralMagic::Size; }
};
#else 
Dummy(SMagic2_t);
#endif

#if Fancy_
#include "Hash_Fancy.hpp"
struct Fancy_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Black Magic BB - Fixed shift";
	static inline constexpr std::string_view author = "Onno Garms and Volker Annuss";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Magic_Bitboards#Fixed_shift_Fancy";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Fancy::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Fancy::Size; }
};
#else 
Dummy(Fancy_t);
#endif

#if Explode_
#include "Exploading.hpp"
struct Explode_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Exploding Bitboards";
	static inline constexpr std::string_view author = "Harald L\x81\xE1 \ben\t"; //Harald Lüßen
	static inline constexpr std::string_view reference = "http://www.open-aurec.com/wbforum/viewtopic.php?f=4&t=4523&start=80";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::ExplodingBoard::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::ExplodingBoard::Size; }
};
#else 
Dummy(Explode_t);
#endif

#if SBAMG_
#include "SBAMG.hpp"
struct SBAMG_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "SBAMG o^(o-3cbn)";
	static inline constexpr std::string_view author = "Syed Fahad";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?t=59845";
	static inline constexpr std::string_view sp_op = "countl_zero, bswap";


	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SBAMG::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::SBAMG::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::SBAMG::Size; }
};
#else 
Dummy(SBAMG_t);
#endif


#if SBAMGNT_
#include "SBAMG_IL.hpp"
struct SBAMGNT_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "SBAMG Inline";
	static inline constexpr std::string_view author = "Syed Fahad and Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?t=59845";
	static inline constexpr std::string_view sp_op = "countl_zero, bswap";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SBAMGInline::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::SBAMGInline::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::SBAMGInline::Size; }
};
#else 
Dummy(SBAMGNT_t);
#endif

#if BinaryNetwork_
#include "BinaryNeuralNetwork.hpp"
struct BinaryNetwork_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Binary Neural Network";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79332";
	static inline constexpr std::string_view sp_op = "pdep_u64, AVX2";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::BNN::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::BNN::Size; }
};
#else 
Dummy(BinaryNetwork_t);
#endif

#if HypQsc_
#include "Hyperbola.hpp"
struct Hyperbola_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Hyperbola Quintessence o^(o-2r)";
	static inline constexpr std::string_view author = "Ryan Mack";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Hyperbola_Quintessence";
	static inline constexpr std::string_view sp_op = "bswap";
	
	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::HyperbolaQsc::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::HyperbolaQsc::Size; }
};
#else 
Dummy(Hyperbola_t);
#endif

#if HypQscNT_
#include "Hyperbola_IL.hpp"
struct HyperbolaNT_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "Hyperbola Quintessence Inline";
	static inline constexpr std::string_view author = "Ryan Mack";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Hyperbola_Quintessence";
	static inline constexpr std::string_view sp_op = "bswap";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::HyperbolaQscInline::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::HyperbolaQscInline::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::HyperbolaQscInline::Size; }
};
#else 
Dummy(HyperbolaNT_t);
#endif

#if Rotate_
#include "Rotated.hpp"
struct Rotate_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Rotated Bitboards";
	static inline constexpr std::string_view author = "Robert Hyatt";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Rotated_Bitboards";
	static inline constexpr std::string_view sp_op = "none";

	static inline void Prepare(uint64_t occ) { Chess_Lookup::RotatedBB::Prepare(occ); }
	static constexpr void Move(int from, int to) { Chess_Lookup::RotatedBB::Move(from, to); }
	static constexpr void Move_Take(int from, int to) { Chess_Lookup::RotatedBB::Move_Take(from, to); }
	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::RotatedBB::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::RotatedBB::Size; }
};
#else 
Dummy(Rotate_t);
#endif


#if Arithm_
#include "SlideArithm.hpp"
struct Arithm_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Slide Arithmetic";
	static inline constexpr std::string_view author = "Jakob Progsch and Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=78693&p=914767&hilit=SlideArithm#p914767";
	static inline constexpr std::string_view sp_op = "bzhi_u64, blsmsk_u64";


	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SlideArithm::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::SlideArithm::Size; }
};
#else 
Dummy(Arithm_t);
#endif



#if Arithm_
#include "SlideArithm_IL.hpp"
struct ArithmNT_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Slide Arithmetic Inline";
	static inline constexpr std::string_view author = "Jakob Progsch and Daniel Inf\x81hr";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=78693&p=914767&hilit=SlideArithm#p914767";
	static inline constexpr std::string_view sp_op = "bzhi_u64, blsmsk_u64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SlideArithmInline::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::SlideArithmInline::Size; }
};
#else 
Dummy(ArithmNT_t);
#endif

#if Kindergarten_
#include "Kindergarten.hpp"
struct Kindergarten_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Kindergarten";
	static inline constexpr std::string_view author = "Urban Koistinen";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/Kindergarten_Bitboards";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Kindergarten::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::Kindergarten::Size; }
};
#else 
Dummy(Kindergarten_t);
#endif

#if PreSchool_
#include "PreSchool.hpp"
struct PreSchool_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "PreSchool";
	static inline constexpr std::string_view author = "Jost Triller";
	static inline constexpr std::string_view reference = "nothing yet";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::PreSchool::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::PreSchool::Size; }
};
#else 
Dummy(PreSchool_t);
#endif


#if Obstrd_
#include "ObstructionDiff.hpp"
struct Obstruct_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Obstruction Difference";
	static inline constexpr std::string_view author = "Michael Hoffmann";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?t=29087";
	static inline constexpr std::string_view sp_op = "countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::ObstructionDiff::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::ObstructionDiff::Size; }
};
#else 
Dummy(Obstruct_t);
#endif


#if ObstrdNT_
#include "ObstructionDiff_IL.hpp"
struct ObstructNT_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "Obstruction Difference Inline";
	static inline constexpr std::string_view author = "Michael Hoffmann";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?t=29087";
	static inline constexpr std::string_view sp_op = "countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::ObstructionDiffInline::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::ObstructionDiffInline::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::ObstructionDiffInline::Size; }
};
#else 
Dummy(ObstructNT_t);
#endif

#if QBB_
#include "QBB.hpp"
struct QBB_t {
	static constexpr bool Supports_Template = true;
	static inline constexpr std::string_view name = "QBBEngine";
	static inline constexpr std::string_view author = "Fabio Gobbato";
	static inline constexpr std::string_view reference = "https://www.chessprogramming.org/QBBEngine";
	static inline constexpr std::string_view sp_op = "countr_zero, countl_zero";
	
	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::QBB::Queen(sq, occ); }
	template <int sq> static uint64_t Queen(uint64_t occ) { return Chess_Lookup::QBB::Queen<sq>(occ); }
	static uint64_t Size() { return Chess_Lookup::QBB::Size; }
};
#else 
Dummy(QBB_t);
#endif


#if GeneticQBB_
#include "GeneticQBB.hpp"
struct GeneticQBB_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "QBBEngine - Shifted Mask";
	static inline constexpr std::string_view author = "Fabio Gobbato";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79005&start=90#p924623";
	static inline constexpr std::string_view sp_op = "countr_zero, countl_zero";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::GeneticQBB::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::GeneticQBB::Size; }
};
#else 
Dummy(GeneticQBB_t);
#endif


#if Sissy_
#include "Sissy.hpp"
struct Sissy_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "SISSY Bitboards";
	static inline constexpr std::string_view author = "Michael Sherwin";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=73083";
	static inline constexpr std::string_view sp_op = "none";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::SISSY::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::SISSY::Size; }
};
#else 
Dummy(Sissy_t);
#endif

#if KGSSB_
#include "KindergartenSuperSissyBoard.hpp"
struct Kgssb_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Kindergarten Super SISSY Bitboards";
	static inline constexpr std::string_view author = "Michael Sherwin";
	static inline constexpr std::string_view reference = "https://www.talkchess.com/forum3/viewtopic.php?f=7&t=81234&start=30";
	static inline constexpr std::string_view sp_op = "imul64";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::KGSSB::Queen(sq, occ); }
	static uint64_t Size() { return Chess_Lookup::KGSSB::Size; }
};
#else 
Dummy(Kgssb_t);
#endif

#if Rotate_
#include "Bitrotation.hpp"
struct Bitrotate_t {
	static constexpr bool Supports_Template = false;
	static inline constexpr std::string_view name = "Bitrotation";
	static inline constexpr std::string_view author = "Daniel Inf\x81hr (dangi12012)";
	static inline constexpr std::string_view reference = "http://www.talkchess.com/forum3/viewtopic.php?f=7&t=79078&start=20";
	static inline constexpr std::string_view sp_op = "ReverseBits";

	static uint64_t Queen(int sq, uint64_t occ) { return Chess_Lookup::Bitrotation::Queen(sq, occ); }

	static uint64_t Size() { return Chess_Lookup::Bitrotation::Size; }
};
#else 
Dummy(Bitrotate_t);
#endif


// Todo - publish pext outperformer X(Gigantua_t);

#define TestAlgo(X)	 \
X(CMagic_t)			 \
X(SMagic_t)			 \
X(SMagic2_t)		 \
X(SBAMG_t)			 \
X(SBAMGNT_t)		 \
X(GaloisField_t)	 \
X(Gigantua_t)	     \
X(Hyperbola_t);		 \
X(HyperbolaNT_t)	 \
X(Genetic8Ray_t)     \
X(Bitrotate_t);		 \
X(BinaryNetwork_t);	 \
X(Explode_t);		 \
X(Switch_t);		 \
X(Loop_t);			 \
X(PextEmu_t);		 \
X(Dumb7_t);			 \
X(Kogge_t);			 \
X(Rotate_t);		 \
X(QBB_t);			 \
X(GeneticQBB_t);     \
X(Bob_t);			 \
X(BobAdvanced_t);	 \
X(Leorik_t);		 \
X(LeorikNT_t);		 \
X(Obstruct_t);		 \
X(ObstructNT_t);	 \
X(GeneticObstructionDiff_t) \
X(GeneticObstructionDiffV2_t) \
X(Arithm_t);		 \
X(ArithmNT_t);		 \
X(Kindergarten_t)	 \
X(PreSchool_t)       \
X(Sissy_t);			 \
X(Kgssb_t);			 \
X(HVar_t);			 \
X(FoldingHash_t)	 \
X(Plain_t);			 \
X(Fancy_t);			 \
X(Pext_t);			 \
X(SplitPext_t);      \
X(Hyper_t);			 

#define ExportAlgo(X) extern "C" __declspec(dllexport) uint64_t __cdecl X##_Queen(int sq, uint64_t occ) { return X::Queen(sq, occ); }
TestAlgo(ExportAlgo); 



#define IsCorrect(X) if constexpr (X::name != "dummy") {if (X::Queen(i, occ) != atk_ref) { std::cout << X::name <<"failed. Reference:\n"<<"Occupy: "<<occ<<"\n"<<_map(occ)<<"\nSolution:\n"<<_map(atk_ref) <<"\nError:\n"<<_map(X::Queen(i, occ)); return false; }}


//Initialize and verify all algorithms
bool VerifyInit() {
	uint64_t occ = 0; 
	
#if Sissy_
	//Todo: Constexpr initializer
	Chess_Lookup::SISSY::Init();
#endif
#if PextSparse_
	Chess_Lookup::PextSparse::Init();
#endif
#if Gigantua_
	Chess_Lookup::Gigantua::Init();
#endif
#if KGSSB_
	Chess_Lookup::KGSSB::Init();
#endif
#if CMagic_
	Chess_Lookup::Correlationmagic::Init();
#endif
#if SMagic2_
	Chess_Lookup::SpectralMagic::Init();
#endif

	std::cout << "Verify Engines...";

	//Todo shift n bits as blockers
	for (int d = 0; d < 50000; d++) {
		if (d < 64 && d!= 0) occ = 0xffull << d;
		#if Hyper_
		   Chess_Lookup::Lookup_Hyper::Prepare(occ);
		#endif
		#if Rotate_
		   Chess_Lookup::RotatedBB::Prepare(occ);
		#endif

		for (int i = 0; i < 64; i++) {
			uint64_t mask = (1ull << i);
			
			if (occ & mask) {
				uint64_t atk_ref = Switch_t::Queen(i, occ);
				uint64_t xray_r = Switch_t::Rook_Xray(i, occ);
				uint64_t xray_b = Switch_t::Bish_Xray(i, occ);
				#if Hyper_
				if (Hyper_t::Rook_Xray(i, occ) != xray_r) { std::cout << Hyper_t::name << "R XRAY failed. Reference:\n" << "Occupy: " << occ << "\n" << _map(occ) << "\nSolution:\n" << _map(xray_r) << "\nError:\n" << _map(Hyper_t::Rook_Xray(i, occ)); return false; }
				if (Hyper_t::Bish_Xray(i, occ) != xray_b) { std::cout << Hyper_t::name << "B XRAY failed. Reference:\n" << "Occupy: " << occ << "\n" << _map(occ) << "\nSolution:\n" << _map(xray_b) << "\nError:\n" << _map(Hyper_t::Bish_Xray(i, occ)); return false; }
				#endif

				TestAlgo(IsCorrect);
			}
		}
		occ = rand64() & rand64();
	}
	std::cout << "OK!\n\n";
	return true;
}

const uint64_t poscnt = 5000000;
thread_local volatile uint64_t opt = 0;

//Assume 50 moves for a board with 8 sliders. (2 already off the board)
template<typename T>
double Get_MLU_EmulateGame()
{
	//Set seeds to be fair to every movegen
	rx = 123456789, ry = 362436069, rz = 521288629;

	auto t1 = std::chrono::high_resolution_clock::now();
	int actualLU = 0;
	for (int i = 0; i < poscnt / 15; i++) {
		uint64_t occ = rand64() & rand64();
		if constexpr (std::is_same<T, Hyper_t>()) {
			Hyper_t::Prepare(occ); //Set init state
		}
		if constexpr (std::is_same<T, Rotate_t>()) {
			Rotate_t::Prepare(occ); //Set init state
		}

		//128 plies
		for (int n = 0; n < 128; n++) {
			int mode = 0;
			for (int r = 0; r < 12; r++) {
				//12 lookups into the position before making a random move...
				if constexpr (std::is_same<T, Hyper_t>()) {
					opt = T::Queen(rand32() & 63, occ);
				}
				else {
					opt = T::Queen(rand32() & 63, occ);
				}
				actualLU++;
			}

			//Make a random move from -> to
			int from = rand32() & 63;
			while (!(1ull << from)) from = rand32() & 63;
			int to = rand32() & 63;
			bool taking = (occ & (1ull << to)) != 0;

			//Move now
			if constexpr (std::is_same<T, Hyper_t>()) {
				if (taking) Hyper_t::Move_Take(from, to);
				else Hyper_t::Move(from, to);
			}
			if constexpr (std::is_same<T, Rotate_t>()) {
				if (taking) Rotate_t::Move_Take(from, to);
				else Rotate_t::Move(from, to);
			}
			
			//Set occupancy
			occ &= ~(1ull << from);
			occ |= (1ull << to);
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	double result = actualLU * 1000.0 / duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	std::cout << T::name << ": \t" << result << "MOps\t" << T::Size() / 1024 << " kB\t" << "Optimal perf: " << T::sp_op << "\n";
	return result;
}



template<typename T>
double Get_MLU()
{
	//Set seeds to be fair to every movegen
	rx = 123456789, ry = 362436069, rz = 521288629;
	std::vector<uint64_t> occs;
	std::vector<uint8_t> squares;

	for (int i = 0; i < poscnt; i++) {
		occs.push_back(rand64() & rand64());

		for (int r = 0; r < 12; r++) { 
			squares.push_back(rand32() % 64);
		}
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	uint64_t dontopt = 0;
	for (int i = 0; i < poscnt; i++) {
		uint64_t occ = occs[i];
		if constexpr (std::is_same<T, Hyper_t>()) {
			Hyper_t::Prepare(occ);
		}
		if constexpr (std::is_same<T, Rotate_t>()) {
			Rotate_t::Prepare(occ);
		}
		for (int r = 0; r < 12; r++) { //12000.0
			dontopt ^= T::Queen(squares[12 * i + r], occ);
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();

	opt = dontopt;
	auto is_tmpl = T::Supports_Template ? "yes" : "no";
	double result = poscnt * 12000.0 / duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	auto perf = std::to_string(result);
	auto table = std::to_string(T::Size() / 8);
	table.append(7 - table.size(), ' ');
	table += " [" + std::to_string(T::Size() / 1024) + "kb]";

	printf("%-35s%-30s%-20s%-25s%-10s%-45s%-50s\n", T::name.data(), perf.c_str(), table.c_str(), T::sp_op.data(), is_tmpl, T::author.data(), T::reference.data());

	return result;
}

static volatile inline int* cache_pressure_buffer = nullptr;

template<typename T>
double Get_MLU_Cache_Pressure()
{
	//Set seeds to be fair to every movegen
	rx = 123456789, ry = 362436069, rz = 521288629;
	std::vector<uint64_t> occs;
	std::vector<uint8_t> squares;

	for (int i = 0; i < poscnt; i++) {
		occs.push_back(rand64() & rand64());

		for (int r = 0; r < 12; r++) {
			squares.push_back(rand32() % 64);
		}
	}
	volatile uint64_t sum = 0;
	constexpr int cache_pressure_size = 64 * 1024 * 1024;
	if (cache_pressure_buffer == nullptr) {
		cache_pressure_buffer = new(std::nothrow) int[cache_pressure_size];
	}
	if (cache_pressure_buffer == nullptr) {
		std::cout << "Could not allocate 1GB buffer";
		return 0;
	}

	auto t1 = std::chrono::high_resolution_clock::now();
	uint64_t dontopt = 0;
	for (int i = 0; i < poscnt; i++) {
		uint64_t occ = occs[i];
		if constexpr (std::is_same<T, Hyper_t>()) {
			Hyper_t::Prepare(occ);
		}
		if constexpr (std::is_same<T, Rotate_t>()) {
			Rotate_t::Prepare(occ);
		}
		for (int r = 0; r < 12; r++) { //12000.0
			dontopt ^= T::Queen(squares[12 * i + r], occ);
		}

		//Emulate random io after a few slider lookups
		if (i % 65536 == 0) {
			for (int m = 0; m < 4; m++) {
				cache_pressure_buffer[rand32() % cache_pressure_size] ^= rand32();
			}
			sum += std::reduce(cache_pressure_buffer, cache_pressure_buffer + cache_pressure_size);
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();

	opt = dontopt;
	auto is_tmpl = T::Supports_Template ? "yes" : "no";
	double result = poscnt * 12000.0 / duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	auto perf = std::to_string(result);
	auto table = std::to_string(T::Size() / 8);
	table.append(7 - table.size(), ' ');
	table += " [" + std::to_string(T::Size() / 1024) + "kb]";

	printf("%-35s%-30s%-20s%-25s%-10s%-45s%-50s\n", T::name.data(), perf.c_str(), table.c_str(), T::sp_op.data(), is_tmpl, T::author.data(), T::reference.data());

	return result;
}

template<typename T>
double Get_MLU_KnownSourceSquare()
{
	//Set seeds to be fair to every movegen
	rx = 123456789, ry = 362436069, rz = 521288629;

	auto t1 = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < poscnt; i++) {
		uint64_t occ = rand64() & rand64();

		if constexpr (std::is_same<T, Hyper_t>()) {
			Hyper_t::Prepare(occ);
		}
		if constexpr (std::is_same<T, Rotate_t>()) {
			Rotate_t::Prepare(occ);
		}

		{
			if constexpr (T::Supports_Template) {
				opt = T::template Queen<55>(occ); opt = T::template Queen<62>(occ); opt = T::template Queen<52>(occ); opt = T::template Queen<37>(occ); opt = T::template Queen<1>(occ); opt = T::template Queen<42>(occ); opt = T::template Queen<32>(occ); opt = T::template Queen<4>(occ);
				opt = T::template Queen<1>(occ); opt = T::template Queen<40>(occ); opt = T::template Queen<19>(occ); opt = T::template Queen<19>(occ); opt = T::template Queen<55>(occ); opt = T::template Queen<34>(occ); opt = T::template Queen<51>(occ); opt = T::template Queen<25>(occ);
				opt = T::template Queen<24>(occ); opt = T::template Queen<5>(occ); opt = T::template Queen<63>(occ); opt = T::template Queen<53>(occ); opt = T::template Queen<21>(occ); opt = T::template Queen<13>(occ); opt = T::template Queen<63>(occ); opt = T::template Queen<18>(occ);
				opt = T::template Queen<23>(occ); opt = T::template Queen<38>(occ); opt = T::template Queen<50>(occ); opt = T::template Queen<39>(occ); opt = T::template Queen<26>(occ); opt = T::template Queen<55>(occ); opt = T::template Queen<44>(occ); opt = T::template Queen<56>(occ);
				opt = T::template Queen<63>(occ); opt = T::template Queen<58>(occ); opt = T::template Queen<0>(occ); opt = T::template Queen<50>(occ); opt = T::template Queen<16>(occ); opt = T::template Queen<45>(occ); opt = T::template Queen<58>(occ); opt = T::template Queen<15>(occ);
				opt = T::template Queen<24>(occ); opt = T::template Queen<16>(occ); opt = T::template Queen<4>(occ); opt = T::template Queen<58>(occ); opt = T::template Queen<17>(occ); opt = T::template Queen<8>(occ); opt = T::template Queen<4>(occ); opt = T::template Queen<38>(occ);
				opt = T::template Queen<63>(occ); opt = T::template Queen<13>(occ); opt = T::template Queen<39>(occ); opt = T::template Queen<6>(occ); opt = T::template Queen<26>(occ); opt = T::template Queen<27>(occ); opt = T::template Queen<2>(occ); opt = T::template Queen<37>(occ);
				opt = T::template Queen<43>(occ); opt = T::template Queen<55>(occ); opt = T::template Queen<52>(occ); opt = T::template Queen<3>(occ); opt = T::template Queen<48>(occ); opt = T::template Queen<17>(occ); opt = T::template Queen<4>(occ); opt = T::template Queen<15>(occ);
			}
			else {
				opt = T::Queen(55, occ); opt = T::Queen(62, occ); opt = T::Queen(52, occ); opt = T::Queen(37, occ); opt = T::Queen(1, occ); opt = T::Queen(42, occ); opt = T::Queen(32, occ); opt = T::Queen(4, occ);
				opt = T::Queen(1, occ); opt = T::Queen(40, occ); opt = T::Queen(19, occ); opt = T::Queen(19, occ); opt = T::Queen(55, occ); opt = T::Queen(34, occ); opt = T::Queen(51, occ); opt = T::Queen(25, occ);
				opt = T::Queen(24, occ); opt = T::Queen(5, occ); opt = T::Queen(63, occ); opt = T::Queen(53, occ); opt = T::Queen(21, occ); opt = T::Queen(13, occ); opt = T::Queen(63, occ); opt = T::Queen(18, occ);
				opt = T::Queen(23, occ); opt = T::Queen(38, occ); opt = T::Queen(50, occ); opt = T::Queen(39, occ); opt = T::Queen(26, occ); opt = T::Queen(55, occ); opt = T::Queen(44, occ); opt = T::Queen(56, occ);
				opt = T::Queen(63, occ); opt = T::Queen(58, occ); opt = T::Queen(0, occ); opt = T::Queen(50, occ); opt = T::Queen(16, occ); opt = T::Queen(45, occ); opt = T::Queen(58, occ); opt = T::Queen(15, occ);
				opt = T::Queen(24, occ); opt = T::Queen(16, occ); opt = T::Queen(4, occ); opt = T::Queen(58, occ); opt = T::Queen(17, occ); opt = T::Queen(8, occ); opt = T::Queen(4, occ); opt = T::Queen(38, occ);
				opt = T::Queen(63, occ); opt = T::Queen(13, occ); opt = T::Queen(39, occ); opt = T::Queen(6, occ); opt = T::Queen(26, occ); opt = T::Queen(27, occ); opt = T::Queen(2, occ); opt = T::Queen(37, occ);
				opt = T::Queen(43, occ); opt = T::Queen(55, occ); opt = T::Queen(52, occ); opt = T::Queen(3, occ); opt = T::Queen(48, occ); opt = T::Queen(17, occ); opt = T::Queen(4, occ); opt = T::Queen(15, occ);
			}
		}
		
	}
	auto is_tmpl = T::Supports_Template ? "yes" : "no";
	auto t2 = std::chrono::high_resolution_clock::now();
	double result = poscnt * 64000.0 / duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	auto perf = std::to_string(result);
	auto table = std::to_string(T::Size() / 8);
	table.append(7 - table.size(), ' ');
	table += " [" + std::to_string(T::Size() / 1024) + "kb]";

	printf("%-35s%-30s%-20s%-25s%-10s%-45s%-50s\n", T::name.data(), perf.c_str(), table.c_str(), T::sp_op.data(), is_tmpl, T::author.data(), T::reference.data());
	
	return result;
}

typedef std::tuple<std::string_view, int, double> Thread_Perf_t;

template<typename T>
Thread_Perf_t Get_MLU_Threaded()
{
	const int processor_count = std::thread::hardware_concurrency() + 8;
	//Warmup once! - VERY important
	{
		uint32_t x = rand32();
		uint32_t y = rand32();
		uint32_t z = rand32();

		for (int n = 0; n < poscnt / 8; n++) {
			uint64_t occ = rand64_state(x, y, z) & rand64_state(x, y, z);

			if constexpr (std::is_same<T, Hyper_t>()) {
				Hyper_t::Prepare(occ);
			}
			if constexpr (std::is_same<T, Rotate_t>()) {
				Rotate_t::Prepare(occ);
			}
			for (int r = 0; r < 64; r++) {
				opt = T::Queen(r, occ);
			}
		}
	}
	double nano_ref = 0;

	//Loop of multithreaded scaling

	int bestThread = 1;
	double bestLUPerf = 0;

	std::cout << "\n" << T::name << " - " << T::Size() / 1024 << " kB\t""\n";
	std::cout << "\tthreads\tspeed\tscaling\tMegalookups/s\n";
	std::vector<std::thread> workers;
	std::vector<std::tuple<uint32_t, uint32_t, uint32_t>> seeds;
	for (int i = 1; i <= processor_count; i++) {

		for (int I = 0; I < i; I++) seeds.push_back({ rand32(), rand32(), rand32() });

		auto t1 = std::chrono::high_resolution_clock::now();
		

		for (int I = 0; I < i; I++) {
			workers.push_back(std::thread([I, seeds]()
			{
				uint32_t x = std::get<0>(seeds[I]);
				uint32_t y = std::get<1>(seeds[I]);
				uint32_t z = std::get<2>(seeds[I]);
				volatile uint64_t topt = 0;
				uint64_t local_opt = 0;

				for (int n = 0; n < poscnt / 16; n++) {
					uint64_t occ = rand64_state(x, y, z) & rand64_state(x, y, z);

					if constexpr (std::is_same<T, Hyper_t>()) {
						Hyper_t::Prepare(occ);
					}
					if constexpr (std::is_same<T, Rotate_t>()) {
						Rotate_t::Prepare(occ);
					}
					Loop64(r, {
							if constexpr (T::Supports_Template)
							{
								local_opt ^= T::template Queen<r>(occ);
							}
							else {
								local_opt ^= T::Queen(r, occ);
							}
						});
				}
				topt = local_opt;
				topt = local_opt;
			}));
		}
		//Join all threads
		for (int I = 0; I < i; I++) workers[I].join();

		auto t2 = std::chrono::high_resolution_clock::now();
		workers.clear(); seeds.clear();
		if (i == 1) nano_ref = static_cast<double>(duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

		auto nano_current = static_cast<double>(duration_cast<std::chrono::nanoseconds>(t2 - t1).count());

		auto MLUps_ref = 1 * poscnt / 16.0 * 64000.0 / nano_ref;
		auto MLUps = i * poscnt / 16.0 * 64000.0 / nano_current; //64000.0 = 64 lookup + nano to micro = MLUps

		auto work_factor = MLUps / MLUps_ref;
		auto scaling = work_factor / i;

		if (MLUps > bestLUPerf) {
			bestLUPerf = MLUps;
			bestThread = i;
		}

		std::cout << "\t" <<i<<"\t" << work_factor << "\t" << scaling*100 << "%\t" << MLUps << "\n";
	}

	//double result = poscnt * processor_count * 64000.0 / duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	//std::cout << T::name << ": \t" << result << "MOps\t" << T::Size() / 1024 << " kB\t" << "Optimal perf: " << T::sp_op << "\n";
	return { T::name, bestThread, bestLUPerf };
}

void PrintPerf(std::vector<Thread_Perf_t>& mt_res) {
	std::cout << "\n\nSummary:\n";
	printf("%-35s%-30s%-20s\n", "Name", "Performance [MQueens/s]", "Threads");

	std::sort(mt_res.begin(), mt_res.end(), [](const Thread_Perf_t& a, const Thread_Perf_t& b) -> bool
		{
			return std::get<2>(a) > std::get<2>(b);
		});

	for (auto& r : mt_res)
	{
		auto perf = std::to_string(std::get<2>(r));
		auto threads = std::to_string(std::get<1>(r));
		printf("%-35s%-30s%-20s\n", std::get<0>(r).data(), perf.data(), threads.data());
	}
}

																												  
#define Norm(X) if constexpr (X::name != "dummy")		    { Get_MLU<X>(); }									  //Random pos, Random occupation, 1 Thread
#define NormTTPressure(X) if constexpr (X::name != "dummy") { Get_MLU_Cache_Pressure<X>(); }					  //Random pos, Random occupation, 1 Thread
#define NormSquare(X) if constexpr (X::name != "dummy")	    { Get_MLU_KnownSourceSquare<X>(); }					  //Known  pos, Random occupation, 1 Thread
#define Multithreaded(X) if constexpr (X::name != "dummy")  { mt_res.push_back(Get_MLU_Threaded<X>()); }		  //Random pos, Random occupation, N Threads
#define Emulated(X) if constexpr (X::name != "dummy")	    { Get_MLU_EmulateGame<X>(); }						  //Random pos, Emulated game occ, 1 Thread

void GetPerf() {
	//std::cout << "\nMillion Lookups/s Known Squares, Random Occupation/s:\n";
	//printf("%-35s%-30s%-20s%-25s%-10s%-45s%s\n", "Name", "Performance [MQueens/s]", "Tablesize", "Dependencies", "Template", "Author", "Reference");
	//TestAlgo(NormSquare);

	std::cout << "\nMillion Lookups/s Random Squares, Random Occupation, Transposition Table Cache Pressure Simulation:\n";
	printf("%-35s%-30s%-20s%-25s%-10s%-45s%s\n", "Name", "Performance [MQueens/s]", "Tablesize", "Dependencies", "Template", "Author", "Reference");
	TestAlgo(Norm);

	std::cout << "\n\nPLEASE COPY PASTE ABOVE OUTPUT and share here:\n http://www.talkchess.com/forum3/posting.php?mode=reply&f=7&t=79005";

	//std::cout << "\nMegalookups Multithreaded Random Positions/s:\n";
	//std::vector<Thread_Perf_t> mt_res;
	//TestAlgo(Multithreaded);
	//PrintPerf(mt_res);

	//TestAlgo(Emulated);
}

constexpr std::array<int, 3> d = []()
{
	std::array<int, 3> val = { 1,2,3 };
	return val;
}();

int main() {

	auto a = Chess_Lookup::GaloisField::Queen(0,0);
	
	VerifyInit();
	PrintBrand();


	GetPerf();

	return 0;
}