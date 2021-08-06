#pragma once

class IndexBuffer
{
private:
	unsigned int id;
	unsigned int count;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void FillBuffer(const unsigned int* data, unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return count; }
};