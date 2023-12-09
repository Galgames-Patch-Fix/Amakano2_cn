

uint32_t GenKey(uint32_t uiSizeCst)
{
	return (((uiSizeCst / 4) * uiSizeCst) << (uiSizeCst % 4)) * (uint32_t)0x4673;
}

int main()
{
	std::vector<std::wstring> file_list;
	GetAllFileNameW(L"cst/", file_list);

	for (auto& file_name : file_list )
	{
		Mem cst_mem(L"cst/" + file_name);
		uint32_t cst_size = cst_mem.Size();
		uint32_t cst_key = GenKey(cst_size);
		uint32_t* cst_ptr = (uint32_t*)cst_mem.Ptr();

		uint32_t* cst_data_ptr = cst_ptr + 4;
		uint32_t cst_data_size = cst_size - (4 * 4);
		uint32_t cst_data_dec_size = 0x8;
		for (size_t round = 0; round < (cst_data_size / 4); round++)
		{
			cst_data_ptr[round] ^= cst_key;
			cst_data_dec_size += 0x4;
			cst_key += cst_data_dec_size;
		}

		cst_mem.Save(L"cst_dec/" + file_name);
	}
}